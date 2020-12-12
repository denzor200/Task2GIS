#ifndef INC_AST_VALUE_DEF_HPP
#define INC_AST_VALUE_DEF_HPP

#include "ast.hpp"
#include "value.hpp"
#include <boost/spirit/home/x3.hpp>

namespace json_client {
namespace parser {
    using x3::double_;
    using x3::int_;

    void add_keywords()
    {
        // TODO: implement this
    }

    struct value_class;
    struct array_class;

    typedef x3::rule<value_class, ast::value> value_type;
    typedef x3::rule<array_class, ast::array> array_type;

    value_type const value("value");
    array_type const array("array");

    auto const value_def = int_ | double_ | array; // TODO: парсинг строки
    auto const array_def = x3::lit('[')
        > -(value % ',')
        > x3::lit(']');

    // TODO: вспомнить чем отличается ">" от ">>"
    // TODO: вспомнить про x3::lit

    BOOST_SPIRIT_DEFINE(value, array);

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
