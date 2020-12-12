#ifndef INC_VALUE_HPP
#define INC_VALUE_HPP

#include "ast/value.hpp"

// TODO: перевести доки

namespace json {

class array;

/**
 * @class value
 * @brief Значение JSON, представленное как класс C++.
 */
class value {
public:
    /// Это перечисление представляет различные типы значений JSON.
    enum value_type {
        /// значение типа "Number"
        Number,
        /// значение типа "String"
        String,
        /// значение типа "Object"
        Object,
        /// значение типа "Array"
        Array,
        /// значение типа "Null"
        Null
    };

    /// <summary>
    /// Constructor creating a null value
    /// </summary>
    value() = default;

    /// <summary>
    /// Constructor creating a JSON number value
    /// </summary>
    /// <param name="value">The C++ value to create a JSON value from</param>
    value(int32_t value);

    /// <summary>
    /// Constructor creating a JSON number value
    /// </summary>
    /// <param name="value">The C++ value to create a JSON value from</param>
    value(uint32_t value);

    /// <summary>
    /// Constructor creating a JSON number value
    /// </summary>
    /// <param name="value">The C++ value to create a JSON value from</param>
    value(int64_t value);

    /// <summary>
    /// Constructor creating a JSON number value
    /// </summary>
    /// <param name="value">The C++ value to create a JSON value from</param>
    value(uint64_t value);

    /// <summary>
    /// Constructor creating a JSON number value
    /// </summary>
    /// <param name="value">The C++ value to create a JSON value from</param>
    value(double value);

    /// <summary>
    /// Constructor creating a JSON string value
    /// </summary>
    /// <param name="value">The C++ value to create a JSON value from, a C++ STL string of the platform-native character
    /// width</param> <remarks> This constructor has O(n) performance because it tries to determine if specified string
    /// has characters that should be properly escaped in JSON. <remarks>
    explicit value(std::string value);

    /// <summary>
    /// Copy constructor
    /// </summary>
    value(const value&);

    /// <summary>
    /// Move constructor
    /// </summary>
    value(value&&) noexcept;

    /// <summary>
    /// Assignment operator.
    /// </summary>
    /// <returns>The JSON value object that contains the result of the assignment.</returns>
    value& operator=(const value&);

    /// <summary>
    /// Move assignment operator.
    /// </summary>
    /// <returns>The JSON value object that contains the result of the assignment.</returns>
    value& operator=(value&&) noexcept;

    /// <summary>
    /// Creates a null value
    /// </summary>
    /// <returns>A JSON null value</returns>
    static value null();

    /// <summary>
    /// Creates a number value
    /// </summary>
    /// <param name="value">The C++ value to create a JSON value from</param>
    /// <returns>A JSON number value</returns>
    static value number(double value);

    /// <summary>
    /// Creates a number value
    /// </summary>
    /// <param name="value">The C++ value to create a JSON value from</param>
    /// <returns>A JSON number value</returns>
    static value number(int32_t value);

    /// <summary>
    /// Creates a number value
    /// </summary>
    /// <param name="value">The C++ value to create a JSON value from</param>
    /// <returns>A JSON number value</returns>
    static value number(uint32_t value);

    /// <summary>
    /// Creates a number value
    /// </summary>
    /// <param name="value">The C++ value to create a JSON value from</param>
    /// <returns>A JSON number value</returns>
    static value number(int64_t value);

    /// <summary>
    /// Creates a number value
    /// </summary>
    /// <param name="value">The C++ value to create a JSON value from</param>
    /// <returns>A JSON number value</returns>
    static value number(uint64_t value);

    /// <summary>
    /// Creates a string value
    /// </summary>
    /// <param name="value">The C++ value to create a JSON value from</param>
    /// <returns>A JSON string value</returns>
    /// <remarks>
    /// This overload has O(n) performance because it tries to determine if
    /// specified string has characters that should be properly escaped in JSON.
    /// </remarks>
    static value string(std::string value);

    /// <summary>
    /// Creates an empty JSON array
    /// </summary>
    /// <returns>An empty JSON array value</returns>
    static json::value array();

    /// <summary>
    /// Creates a JSON array
    /// </summary>
    /// <param name="size">The initial number of elements of the JSON value</param>
    /// <returns>A JSON array value</returns>
    static json::value array(size_t size);

    /// <summary>
    /// Tests for the presence of a field.
    /// </summary>
    /// <param name="key">The name of the field</param>
    /// <returns>True if the field exists, false otherwise.</returns>
    bool has_field(const std::string& key) const;

    /// <summary>
    /// Accesses the type of JSON value the current value instance is
    /// </summary>
    /// <returns>The value's type</returns>
    json::value::value_type type() const;

    /// <summary>
    /// Is the current value a number value?
    /// </summary>
    /// <returns><c>true</c> if the value is a number value, <c>false</c> otherwise</returns>
    bool is_number() const;

    /// <summary>
    /// Is the current value represented as an integer number value?
    /// </summary>
    /// <remarks>
    /// Note that if a json value is a number but represented as a double it can still
    /// be retrieved as a integer using as_integer(), however the value will be truncated.
    /// </remarks>
    /// <returns><c>true</c> if the value is an integer value, <c>false</c> otherwise.</returns>
    bool is_integer() const;

    /// <summary>
    /// Is the current value represented as an double number value?
    /// </summary>
    /// <remarks>
    /// Note that if a json value is a number but represented as a int it can still
    /// be retrieved as a double using as_double().
    /// </remarks>
    /// <returns><c>true</c> if the value is an double value, <c>false</c> otherwise.</returns>
    bool is_double() const;

    /// <summary>
    /// Is the current value a string value?
    /// </summary>
    /// <returns><c>true</c> if the value is a string value, <c>false</c> otherwise</returns>
    bool is_string() const;

    /// <summary>
    /// Is the current value an array?
    /// </summary>
    /// <returns><c>true</c> if the value is an array, <c>false</c> otherwise</returns>
    bool is_array() const;

    /// <summary>
    /// Is the current value an object?
    /// </summary>
    /// <returns><c>true</c> if the value is an object, <c>false</c> otherwise</returns>
    bool is_object() const;

    /// <summary>
    /// Gets the number of children of the value.
    /// </summary>
    /// <returns>The number of children. 0 for all non-composites.</returns>
    size_t size() const;

    /// <summary>
    /// Parses a string and construct a JSON value.
    /// </summary>
    /// <param name="value">The C++ value to create a JSON value from, a C++ STL string of the
    /// platform-native character width</param>
    static value parse(const std::string& value);

    /// <summary>
    /// Serializes the current JSON value to a C++ string.
    /// </summary>
    /// <returns>A string representation of the value</returns>
    std::string serialize() const;

    /// <summary>
    /// Converts the JSON value to a C++ double, if and only if it is a number value.
    /// Throws <see cref="json_exception"/>  if the value is not a number
    /// </summary>
    /// <returns>A double representation of the value</returns>
    double as_double() const;

    /// <summary>
    /// Converts the JSON value to a C++ integer, if and only if it is a number value.
    /// Throws <see cref="json_exception"/> if the value is not a number
    /// </summary>
    /// <returns>An integer representation of the value</returns>
    int as_integer() const;

    /// <summary>
    /// Converts the JSON value to a json array, if and only if it is an array value.
    /// </summary>
    /// <remarks>The returned <c>json::array</c> should have the same or shorter lifetime as <c>this</c></remarks>
    /// <returns>An array representation of the value</returns>
    json::array& as_array();

    /// <summary>
    /// Converts the JSON value to a json array, if and only if it is an array value.
    /// </summary>
    /// <remarks>The returned <c>json::array</c> should have the same or shorter lifetime as <c>this</c></remarks>
    /// <returns>An array representation of the value</returns>
    const json::array& as_array() const;

    /// <summary>
    /// Converts the JSON value to a C++ STL string, if and only if it is a string value.
    /// </summary>
    /// <returns>A C++ STL string representation of the value</returns>
    const std::string& as_string() const;

    /// <summary>
    /// Accesses an element of a JSON array. Throws when index out of bounds.
    /// </summary>
    /// <param name="index">The index of an element in the JSON array.</param>
    /// <returns>A reference to the value.</returns>
    json::value& at(size_t index);

    /// <summary>
    /// Accesses an element of a JSON array. Throws when index out of bounds.
    /// </summary>
    /// <param name="index">The index of an element in the JSON array.</param>
    /// <returns>A reference to the value.</returns>
    const json::value& at(size_t index) const;

    /// <summary>
    /// Accesses an element of a JSON object. If the key doesn't exist, this method throws.
    /// </summary>
    /// <param name="key">The key of an element in the JSON object.</param>
    /// <returns>If the key exists, a reference to the value.</returns>
    json::value& at(const std::string& key);

    /// <summary>
    /// Accesses an element of a JSON object. If the key doesn't exist, this method throws.
    /// </summary>
    /// <param name="key">The key of an element in the JSON object.</param>
    /// <returns>If the key exists, a reference to the value.</returns>
    const json::value& at(const std::string& key) const;

private:
    json_client::ast::value m_value; //{ json_client::ast::null };
};

class json_exception : public std::exception {
private:
    std::string _message;

public:
    json_exception(const char* const message)
        : _message(message)
    {
    }
    json_exception(std::string&& message)
        : _message(std::move(message))
    {
    }

    // Must be narrow string because it derives from std::exception
    const char* what() const noexcept { return _message.c_str(); }
};

/// <summary>
/// A JSON array represented as a C++ class.
/// </summary>
class array {
    typedef std::vector<json::value> storage_type;

public:
    typedef storage_type::iterator iterator;
    typedef storage_type::const_iterator const_iterator;
    typedef storage_type::reverse_iterator reverse_iterator;
    typedef storage_type::const_reverse_iterator const_reverse_iterator;
    typedef storage_type::size_type size_type;

private:
    array() = default;
    array(size_type size);
    array(storage_type elements);

public:
    /// <summary>
    /// Gets the beginning iterator element of the array
    /// </summary>
    /// <returns>An <c>iterator</c> to the beginning of the JSON array.</returns>
    iterator begin();

    /// <summary>
    /// Gets the beginning const iterator element of the array.
    /// </summary>
    /// <returns>A <c>const_iterator</c> to the beginning of the JSON array.</returns>
    const_iterator begin() const;

    /// <summary>
    /// Gets the end iterator element of the array
    /// </summary>
    /// <returns>An <c>iterator</c> to the end of the JSON array.</returns>
    iterator end();

    /// <summary>
    /// Gets the end const iterator element of the array.
    /// </summary>
    /// <returns>A <c>const_iterator</c> to the end of the JSON array.</returns>
    const_iterator end() const;

    /// <summary>
    /// Gets the number of elements of the array.
    /// </summary>
    /// <returns>The number of elements.</returns>
    size_type size() const;

private:
    storage_type m_elements;
};

inline array::iterator array::begin() { return m_elements.begin(); }

inline array::const_iterator array::begin() const { return m_elements.cbegin(); }

inline array::iterator array::end() { return m_elements.end(); }

inline array::const_iterator array::end() const { return m_elements.cend(); }

inline array::size_type array::size() const { return m_elements.size(); }

inline value value::null()
{
    // TODO: Implement this
}

inline value value::number(double value)
{
    // TODO: Implement this
}

inline value value::number(int32_t value)
{
    // TODO: Implement this
}

inline value value::number(uint32_t value)
{
    // TODO: Implement this
}

inline value value::number(int64_t value)
{
    // TODO: Implement this
}

inline value value::number(uint64_t value)
{
    // TODO: Implement this
}

inline value value::string(std::string value)
{
    // TODO: Implement this
}

inline value value::array()
{
    // TODO: Implement this
}

inline value value::array(size_t size)
{
    // TODO: Implement this
}

inline bool value::has_field(const std::string& key) const
{
    // TODO implement this
}

inline value::value_type value::type() const
{
    // TODO implement this
}

inline bool value::is_number() const { return type() == Number; }

inline bool value::is_integer() const
{
    // TODO implement this
}

inline bool value::is_double() const
{
    // TODO implement this
}

inline bool value::is_string() const { return type() == String; }

inline bool value::is_array() const { return type() == Array; }

inline bool value::is_object() const { return type() == Object; }

inline size_t value::size() const
{
    // TODO implement this
}

inline double value::as_double() const
{
    // TODO implement this
}

inline int value::as_integer() const
{
    // TODO implement this
}

inline array& value::as_array()
{
    // TODO implement this
}

inline const array& value::as_array() const
{
    // TODO implement this
}

inline const std::string& value::as_string() const
{
    // TODO implement this
}

inline value& value::at(size_t index)
{
    // TODO implement this
}

inline const value& value::at(size_t index) const
{
    // TODO implement this
}

inline value& value::at(const std::string& key)
{
    // TODO implement this
}

inline const value& value::at(const std::string& key) const
{
    // TODO implement this
}

} // end of namespace json

#endif // INC_VALUE_HPP
