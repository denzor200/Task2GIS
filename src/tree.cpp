#include "tree.h"
#include "json/value.h"
#include <algorithm>
#include <optional>

tree::tree(int value, std::vector<tree> childs) noexcept
    : m_value(std::move(value))
    , m_childs(std::move(childs))
{
}

tree::tree(double value, std::vector<tree> childs) noexcept
    : m_value(std::move(value))
    , m_childs(std::move(childs))
{
}

tree::tree(std::string value, std::vector<tree> childs) noexcept
    : m_value(std::move(value))
    , m_childs(std::move(childs))
{
}

tree tree::parse(const json::value& root)
{
    auto output = std::optional<tree> {};
    const auto& value = root.at(VALUE_FN);
    if (value.is_double())
        output = tree { value.as_double() };
    else if (value.is_integer())
        output = tree { value.as_integer() };
    else if (value.is_string())
        output = tree { value.as_string() };
    else {
        // TODO: throw exception
    }

    if (root.has_field(CHILDS_FN)) {
        const auto& childs = root.at(CHILDS_FN).as_array();
        output->childs().reserve(childs.size());
        std::transform(childs.begin(), childs.end(), ///
            std::back_inserter(output->childs()), &tree::parse);
    }

    return output.value();
}

json::value tree::serialize() const
{
    auto output = json::value {};

    return output;
}
