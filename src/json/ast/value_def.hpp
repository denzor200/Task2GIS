#ifndef INC_AST_VALUE_DEF_HPP
#define INC_AST_VALUE_DEF_HPP

#include "ast.hpp"
#include "common.hpp"
#include "value.hpp"
#include <boost/spirit/home/x3.hpp>
#include <mutex>

namespace json_client {
namespace parser {
    using x3::char_;
    using x3::double_;
    using x3::int_;
    using x3::lexeme;

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

    typedef x3::rule<value_class, ast::value> value_type;
    typedef x3::rule<array_class, ast::array> array_type;
    typedef x3::rule<quoted_class, std::string> quoted_type;
    typedef x3::rule<null_class, ast::null> null_type;

    value_type const value("value");
    array_type const array("array");
    quoted_type const quoted("quoted");
    null_type const null("null");

    auto const null_def = lexeme[null_kw];
    auto const value_def = null | quoted | double_ | int_ | array; // TODO: парсинг объекта
    auto const array_def = x3::lit('[')
        > -(value % ',')
        > x3::lit(']');
    auto const quoted_def = lexeme['"' >> *(unfinished_guard_ | (esc_guard_) | (char_ - '"')) >> '"'];

    // TODO: вспомнить чем отличается ">" от ">>"
    // TODO: вспомнить про x3::lit

    BOOST_SPIRIT_DEFINE(value, array, quoted, null);

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
