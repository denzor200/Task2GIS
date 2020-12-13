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

    struct error_handler_base {
        template <typename Iterator, typename Exception, typename Context>
        x3::error_handler_result on_error(
            Iterator& first, Iterator const& last, Exception const& x, Context const& context)
        {
            std::string message = x.which() + " here:";
            auto& error_handler = x3::get<error_handler_tag>(context).get();
            error_handler(x.where(), message);
            return x3::error_handler_result::fail;
        }
    };
} // end of namespace parser
} // end of namespace json_client

#endif // INC_AST_ERROR_HANDLER_HPP
