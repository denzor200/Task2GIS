#ifndef INC_AST_VALUE_DEF_HPP
#define INC_AST_VALUE_DEF_HPP

#include "ast.hpp"
#include "ast_adapted.hpp"
#include "common.hpp"
#include "error_handler.hpp"
#include "value.hpp"
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include <mutex>

namespace json_client {
namespace parser {
    using x3::char_;
    using x3::double_;
    using x3::int_;
    using x3::lexeme;
    using x3::lit;

    auto const unfinished_guard_ = unfinished_guard {};
    auto const esc_guard_ = esc_guard {};
    x3::symbols<> null_kw;

    void add_keywords()
    {
        static std::once_flag once;
        std::call_once(once, [&]() {
            null_kw.add("null");

            // TODO: escape-символы
        });
    }

    struct value_class;
    struct array_class;
    struct quoted_class;
    struct null_class;
    struct member_pair_class;
    struct object_class;

    typedef x3::rule<value_class, ast::value> value_type;
    typedef x3::rule<array_class, ast::array> array_type;
    typedef x3::rule<quoted_class, std::string> quoted_type;
    typedef x3::rule<null_class, ast::null> null_type;
    typedef x3::rule<member_pair_class, std::pair<std::string, ast::value>> member_pair_type;
    typedef x3::rule<object_class, ast::object> object_type;

    value_type const value("value");
    array_type const array("array");
    quoted_type const quoted("quoted");
    null_type const null("null");
    member_pair_type const member_pair("member_pair");
    object_type const object("object");

    auto const null_def = lexeme[null_kw];
    auto const value_def = null | quoted | double_ | int_ | array | object;
    auto const array_def = lit('[')
        > -(value % ',')
        > lit(']');
    auto const quoted_def = lexeme['"' >> *(unfinished_guard_ | esc_guard_ | (char_ - '"')) >> '"'];
    auto const member_pair_def = quoted
        >> ':'
        >> value;
    auto const object_def = lit('{')
        >> -(member_pair % ',')
        >> lit('}');

    // TODO: вспомнить чем отличается ">" от ">>"
    // TODO: вспомнить про x3::lit

    BOOST_SPIRIT_DEFINE(value, array, quoted, null, member_pair, object);

    struct value_class : error_handler_base, x3::annotate_on_success {
    };
} // end of namespace parser
} // end of namespace json_client

namespace json_client {
parser::value_type const& value()
{
    parser::add_keywords();
    return parser::value;
}
} // end of namespace json_client

#endif // INC_AST_VALUE_DEF_HPP
