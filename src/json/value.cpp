#include "value.h"
#include "ast/config.hpp"
#include "ast/value.hpp"
#include "detail/generator.h"
#include <boost/range/adaptors.hpp>

using iterator_type = std::string::const_iterator;
using ast_program = json_client::ast::value;

namespace {
struct AstHandler {
    typedef json::value result_type;

    json::value operator()(int arg) const
    {
        return json::value::number(arg);
    }
    json::value operator()(double arg) const
    {
        return json::value::number(arg);
    }
    json::value operator()(const std::string& arg) const
    {
        return json::value::string(arg);
    }
    json::value operator()(const json_client::ast::array& arg) const
    {
        auto ret = json::value::array(arg.size());
        for (const auto& val : arg | boost::adaptors::indexed(0)) {
            ret.at(val.index()) = boost::apply_visitor(*this, val.value());
        }
        return ret;
    }
};
}; // end of anonymous namespace

json::value::value(int value)
    : m_value(value)
{
}

json::value::value(double value)
    : m_value(value)
{
}

json::value::value(std::string value)
    : m_value(value)
{
}

json::value json::value::parse(const std::string& value)
{
    ast_program program;
    std::stringstream ess;

    iterator_type iter = value.cbegin();
    iterator_type end = value.cend();

    using boost::spirit::x3::with;
    using json_client::parser::error_handler_type;
    error_handler_type error_handler(iter, end, ess);

    auto const parser = with<json_client::parser::error_handler_tag>(std::ref(error_handler))
        [json_client::value()];

    boost::spirit::x3::ascii::space_type space;

    if (!phrase_parse(iter, end, parser, space, program) || iter != end) {
        auto errStr = ess.str();
        if (errStr.empty())
            errStr = "can't parse";
        throw json_exception(std::move(errStr));
    }

    return boost::apply_visitor(AstHandler {}, program);
}

std::string json::value::serialize() const
{
    detail::generator gen(*this);
    gen.generate();
    return gen.string();
}

json::array::array(json::array::size_type size)
    : m_elements(size)
{
}
