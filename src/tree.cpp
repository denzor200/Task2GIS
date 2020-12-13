#include "tree.h"
#include "json/value.h"
#include <algorithm>
#include <boost/range/adaptors.hpp>
#include <optional>

tree::tree(int value, std::vector<tree> childs) noexcept
    : m_node(std::move(value))
    , m_subnodes(std::move(childs))
{
}

tree::tree(double value, std::vector<tree> childs) noexcept
    : m_node(std::move(value))
    , m_subnodes(std::move(childs))
{
}

tree::tree(std::string value, std::vector<tree> childs) noexcept
    : m_node(std::move(value))
    , m_subnodes(std::move(childs))
{
}

tree tree::parse(const json::value& root)
{
    auto output = std::optional<tree> {};
    const auto& value = root.at(NODE_FN);
    if (value.is_double())
        output = tree { value.as_double() };
    else if (value.is_integer())
        output = tree { value.as_integer() };
    else if (value.is_string())
        output = tree { value.as_string() };
    else {
        // TODO: throw exception
    }

    if (root.has_field(SUBNODES_FN)) {
        const auto& childs = root.at(SUBNODES_FN).as_array();
        output->childs().reserve(childs.size());
        std::transform(childs.begin(), childs.end(), ///
            std::back_inserter(output->childs()), &tree::parse);
    }

    return output.value();
}

json::value tree::serialize() const
{
    auto output = json::value::object();

    std::visit(overloaded {
                   [&](const std::string& arg) {
                       output[NODE_FN] = json::value::string(arg);
                   },
                   [&](int arg) {
                       output[NODE_FN] = json::value::number(arg);
                   },
                   [&](double arg) {
                       output[NODE_FN] = json::value::number(arg);
                   } },
        m_node);

    for (const auto& sub : m_subnodes | boost::adaptors::indexed(0)) {
        if (!output.has_field(SUBNODES_FN))
            output[SUBNODES_FN] = json::value::array(m_subnodes.size());
        auto& childs = output[SUBNODES_FN].as_array();
        childs.at(sub.index()) = sub.value().serialize();
    }

    return output;
}
