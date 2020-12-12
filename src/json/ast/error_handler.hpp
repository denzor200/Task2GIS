#ifndef INC_AST_ERROR_HANDLER_HPP
#define INC_AST_ERROR_HANDLER_HPP

#include "value.hpp"
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>

namespace json_client {
namespace parser {
    namespace x3 = boost::spirit::x3;

    template <typename Iterator>
    using error_handler = x3::error_handler<Iterator>;

    using error_handler_tag = x3::error_handler_tag;
} // end of namespace parser
} // end of namespace json_client

#endif // INC_AST_ERROR_HANDLER_HPP
