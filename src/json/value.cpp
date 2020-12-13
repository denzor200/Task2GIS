#include "value.h"

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
