#ifndef INC_AST_VALUE_HPP
#define INC_AST_VALUE_HPP

#include "ast.hpp"
#include <boost/spirit/home/x3.hpp>

namespace json_client {
namespace x3 = boost::spirit::x3;
namespace parser {
    struct value_class;
    typedef x3::rule<value_class, ast::value> value_type;
    BOOST_SPIRIT_DECLARE(value_type);
} // end of namespace parser

parser::value_type const& value();
} // end of namespace json_client

#endif // INC_AST_VALUE_HPP
