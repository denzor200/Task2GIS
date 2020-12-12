#include "value.h"

json::value::value(int32_t value)
{
    // TODO: Implement this
}

json::value::value(uint32_t value)
{
    // TODO: Implement this
}

json::value::value(int64_t value)
{
    // TODO: Implement this
}

json::value::value(uint64_t value)
{
    // TODO: Implement this
}

json::value::value(double value)
{
    // TODO: Implement this
}

json::value::value(std::string value)
{
    // TODO: Implement this
}

json::value::value(const json::value&)
{
    // TODO: Implement this
}

json::value::value(json::value&&) noexcept
{
    // TODO: Implement this
}

json::value& json::value::operator=(const json::value&)
{
    // TODO: Implement this
}

json::value& json::value::operator=(json::value&&) noexcept
{
    // TODO: Implement this
}

json::value json::value::parse(const std::string& value)
{
    // TODO: Implement this
}

std::string json::value::serialize() const
{
    // TODO: Implement this
}

json::array::array(json::array::size_type size)
    : m_elements(size)
{
}

json::array::array(json::array::storage_type elements)
    : m_elements(std::move(elements))
{
}
