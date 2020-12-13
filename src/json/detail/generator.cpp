#include "generator.h"
#include "json/value.h"
#include <boost/assert.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/range/adaptors.hpp>
#include <iomanip>

using namespace detail;

generator::generator(const json::value& value)
{
    setValueRef(value, 0);
}

void generator::generate()
{
    BOOST_ASSERT(m_value);

    m_ss << std::string(m_level, ' ');

    switch (m_value->type()) {
    case json::value::Null:
        generateNull();
        break;

    case json::value::Number:
        generateNumber();
        break;

    case json::value::String:
        generateString();
        break;

    case json::value::Array:
        generateArray();
        break;

    case json::value::Object:
        generateObject();
        break;

    default:
        throw std::runtime_error("invalid json");
    }
}

void generator::generateNull()
{
    m_ss << "null";
}

void generator::generateNumber()
{
    if (m_value->is_double()) {
        auto d = m_value->as_double();
        if (boost::math::isnan(d)) {
            m_ss << "NaN";
        }
        if (boost::math::isinf(d)) {
            if (d < 0.0) {
                m_ss << '-';
            }
            m_ss << "Infinity";
        } else {
            m_ss << d;
        }
    } else if (m_value->is_integer())
        m_ss << m_value->as_integer();
    else {
        throw std::runtime_error("invalid json");
    }
}

void generator::generateString()
{
    m_ss << std::quoted(m_value->as_string());
}

void generator::generateArray()
{
    m_ss << '[' << std::endl;

    auto prevValue = m_value;
    auto prevLevel = m_level;

    const auto& array = m_value->as_array();
    for (const auto& value : array | boost::adaptors::indexed(0)) {
        setValueRef(value.value(), prevLevel + 1);
        generate();
        m_ss << ((value.index() == array.size() - 1) ? "" : ",") << std::endl;
    }

    setValueRef(*prevValue, prevLevel);
    m_ss << std::string(m_level, ' ') << ']';
}

template <typename T>
class TD;

void generator::generateObject()
{
    m_ss << '{';

    auto prevValue = m_value;
    auto prevLevel = m_level;

    const auto& object = m_value->as_object();
    for (const auto& memPair : object | boost::adaptors::indexed(0)) {
        auto first = json::value::string(memPair.value().first);
        auto second = std::cref(memPair.value().second);

        setValueRef(first, prevLevel + 1);
        generate();

        m_ss << " : ";

        setValueRef(second, prevLevel + 1);
        generate();

        m_ss << ((memPair.index() == object.size() - 1) ? "" : ",") << std::endl;
    }

    setValueRef(*prevValue, prevLevel);
    m_ss << std::string(m_level, ' ') << '}';
}
