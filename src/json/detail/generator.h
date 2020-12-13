#ifndef GENERATOR_H
#define GENERATOR_H

#include <sstream>

namespace json {
class value;
} // end of namespace json

// TODO: docs

namespace detail {
class generator {
    std::stringstream m_ss;

    const json::value* m_value;
    unsigned m_level;

public:
    generator(const json::value& value);

    void generate();

    std::string string() const;

private:
    void generateNull();
    void generateNumber();
    void generateString();
    void generateArray();
    void generateObject();

    void setValueRef(const json::value& value, unsigned level);
};

inline std::string generator::string() const
{
    return m_ss.str();
}

inline void generator::setValueRef(const json::value& value, unsigned level)
{
    m_value = &value;
    m_level = level;
}
} // end of namespace detail

#endif // GENERATOR_H
