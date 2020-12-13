#ifndef INC_AST_COMMON_HPP
#define INC_AST_COMMON_HPP

#include "ast_adapted.hpp"
#include <boost/spirit/home/x3.hpp>

namespace json_client {
namespace x3 = boost::spirit::x3;

struct unfinished_guard : x3::parser<unfinished_guard> {
    using attribute_type = char;

    template <typename Iterator, typename Context, typename RContext, typename Attribute>
    bool parse(Iterator& first, Iterator const& last, Context const& context,
        RContext const& rcontext, Attribute& attr) const
    {
        if (first == last) {
            boost::throw_exception(
                x3::expectation_failure<Iterator>(
                    first, "unfinished string"));
        }
        if (*first == '\n' || *first == '\r') {
            boost::throw_exception(
                x3::expectation_failure<Iterator>(
                    first, "unfinished string"));
        }
        return false;
    }
};

struct esc_guard : x3::parser<esc_guard> {
    using attribute_type = char;

    template <typename Iterator, typename Context, typename RContext, typename Attribute>
    bool parse(Iterator& first, Iterator const& last, Context const& context,
        RContext const& rcontext, Attribute& attr) const
    {
        if (first != last && *first == '\\') {
            boost::throw_exception(
                x3::expectation_failure<Iterator>(
                    first, "invalid escape sequence"));
        }
        return false;
    }
};
} // end of namespace json_client

template <>
struct json_client::x3::get_info<json_client::unfinished_guard> {
    typedef std::string result_type;
    std::string operator()(json_client::unfinished_guard const&) const
    {
        return "unfinished_guard";
    }
};

template <>
struct json_client::x3::get_info<json_client::esc_guard> {
    typedef std::string result_type;
    std::string operator()(json_client::esc_guard const&) const
    {
        return "esc_guard";
    }
};

#endif // INC_AST_COMMON_HPP
