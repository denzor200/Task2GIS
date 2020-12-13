#ifndef INC_AST_AST_HPP
#define INC_AST_AST_HPP

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <deque>

namespace json_client {
namespace x3 = boost::spirit::x3;
namespace ast {
    struct null {
    };
    struct array;
    struct value : x3::variant<null, int, double, std::string, x3::forward_ast<array>> {
        using base_type::base_type;
        using base_type::operator=;
    };
    struct array : std::deque<value> {
    };
} // end of namespace ast
} // end of namespace json_client

#endif // INC_AST_AST_HPP
