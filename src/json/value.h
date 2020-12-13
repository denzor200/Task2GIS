#ifndef INC_VALUE_HPP
#define INC_VALUE_HPP

#include "utils.h"
#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace json {

class value;

/**
 * @class json_exception
 */
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

    const char* what() const noexcept { return _message.c_str(); }
};

/**
 * @class array
 * @brief Массив JSON, представленный как C++ класс.
 */
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

public:
    /**
     * @brief Возвращает итератор, ссылающийся на первый элемент массива
     * @return Итератор, ссылающийся на первый элемент массива
     */
    iterator begin();

    /**
     * @brief Возвращает константный итератор, ссылающийся на первый элемент массива
     * @return Константный итератор, ссылающийся на первый элемент массива
     */
    const_iterator begin() const;

    /**
     * @brief Возвращает итератор, ссылающийся на запредельный элемент массива
     * @return Итератор, ссылающийся на запредельный элемент массива
     */
    iterator end();

    /**
     * @brief Возвращает константный итератор, ссылающийся на запредельный элемент массива
     * @return Константный итератор, ссылающийся на запредельный элемент массива
     */
    const_iterator end() const;

    /**
     * @brief Возвращает количество элементов в массиве
     * @return Количество элементов в массиве
     */
    size_type size() const;

    /**
     * @brief Предоставляет доступ к элементу в массиве.
     * @param index индекс элемента в массиве
     * @throw json_exception если индекс выходит за предел
     * @return ссылка на элемент
     */
    json::value& at(size_type index);

    /**
     * @brief Предоставляет доступ к элементу в массиве.
     * @param index индекс элемента в массиве
     * @throw json_exception если индекс выходит за предел
     * @return ссылка на элемент
     */
    const json::value& at(size_type index) const;

private:
    friend class json::value;
    storage_type m_elements;
};

/**
 * @class object
 * @brief Объект JSON, представленный как C++ класс.
 */
class object {
    typedef std::map<std::string, json::value> storage_type;

public:
    typedef storage_type::iterator iterator;
    typedef storage_type::const_iterator const_iterator;
    typedef storage_type::reverse_iterator reverse_iterator;
    typedef storage_type::const_reverse_iterator const_reverse_iterator;
    typedef storage_type::size_type size_type;

private:
    object() = default;

public:
    /**
     * @brief Возвращает итератор, ссылающийся на первый элемент объекта
     * @return Итератор, ссылающийся на первый элемент объекта
     */
    iterator begin();

    /**
     * @brief Возвращает константный итератор, ссылающийся на первый элемент объекта
     * @return Константный итератор, ссылающийся на первый элемент объекта
     */
    const_iterator begin() const;

    /**
     * @brief Возвращает итератор, ссылающийся на запредельный элемент объекта
     * @return Итератор, ссылающийся на запредельный элемент объекта
     */
    iterator end();

    /**
     * @brief Возвращает константный итератор, ссылающийся на запредельный элемент объекта
     * @return Константный итератор, ссылающийся на запредельный элемент объекта
     */
    const_iterator end() const;

    /**
     * @brief Возвращает количество элементов в объекте
     * @return Количество элементов в объекте
     */
    size_type size() const;

    /**
     * @brief Предоставляет доступ к элементу JSON-объекта.
     * @param key ключ по которому производится поиск элемента
     * @throw json_exception если не найдено
     * @remarks Возвращенный json::value должен иметь такое же или меньшее время жизни, как this
     * @return Ссылка на элемент
     */
    const json::value& at(const std::string& key) const;

    /**
     * @brief Предоставляет доступ к элементу JSON-объекта.
     * @param key ключ по которому производится поиск элемента
     * @remarks Возвращенный json::value должен иметь такое же или меньшее время жизни, как this
     * @return Если ключ существует, ссылка на значение, хранящееся в поле, в противном случае вновь
     * созданное нулевое значение, которое будет сохранено для данного ключа.
     */
    json::value& operator[](const std::string& key);

    /**
     * @brief Возвращает итератор на искомый элемент в JSON-объекте.
     * @param key ключ искомого элемента
     * @return константный итератор, указывающий на значение
     */
    const_iterator find(const std::string& key) const;

private:
    friend class json::value;
    storage_type m_elements;
};

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

    /**
     * @brief Конструктор, создающий значение типа "Null"
     */
    value() = default;

    /**
     * @brief Конструктор, создающий значение типа "Number"
     * @param value Значение C++ из которого создается JSON-значение
     */
    value(int value);

    /**
     * @brief Конструктор, создающий значение типа "Number"
     * @param value Значение C++ из которого создается JSON-значение
     */
    value(double value);

    /**
     * @brief Конструктор, создающий значение типа "String"
     * @param value Значение C++ из которого создается JSON-значение
     * @remarks Этот конструктор работает за O(n), поскольку он пытается определить, есть ли в указанной строке символы, которые должны быть правильно экранированы в JSON.
     */
    explicit value(std::string value);

    /**
     * @brief Копирующий конструктор
     */
    value(const value&) = default;

    /**
     * @brief Перемещающий конструктор
     */
    value(value&&) noexcept = default;

    /**
     * @brief Оператор присваивания
     * @returns JSON-значение, содержащее результат присваивания
     */
    value& operator=(const value&) = default;

    /**
     * @brief Оператор присваивания перемещением
     * @returns JSON-значение, содержащее результат присваивания
     */
    value& operator=(value&&) noexcept = default;

    /**
     * @brief Создает значение типа "null"
     * @return JSON-значение типа "null"
     */
    static value null();

    /**
     * @brief Создает значение типа "number"
     * @param value Значение C++ из которого создается JSON-значение
     * @return JSON-значение типа "number"
     */
    static value number(double value);

    /**
     * @brief Создает значение типа "number"
     * @param value Значение C++ из которого создается JSON-значение
     * @return JSON-значение типа "number"
     */
    static value number(int value);

    /**
     * @brief Создает значение типа "number"
     * @param value Значение C++ из которого создается JSON-значение
     * @remarks Функция работает за O(n), поскольку пытается определить, есть ли в указанной строке символы, которые должны быть правильно экранированы в JSON.
     * @return JSON-значение типа "number"
     */
    static value string(std::string value);

    /**
     * @brief Создает пустое значение типа "array"
     * @return пустое JSON-значение типа "array"
     */
    static json::value array();

    /**
     * @brief Создает значение типа "array"
     * @param size изначальное количество элементов в выходном массиве
     * @return JSON-значение типа "array"
     */
    static json::value array(size_t size);

    /**
     * @brief Создает значение типа "object"
     * @return JSON-значение типа "object"
     */
    static json::value object();

    /**
     * @brief Проверяет на наличие поля
     * @param key имя поля
     * @return false если поле не найдено (или если текущее JSON-значение не является объектом)
     */
    bool has_field(const std::string& key) const;

    /**
     * @brief Доступ к JSON-типу текущего значения
     * @return Тип значения
     */
    json::value::value_type type() const;

    /**
     * @brief Текущее значение является числовым значением?
     * @return false если не является
     */
    bool is_number() const;

    /**
     * @brief Представлено ли текущее значение как целочисленное значение?
     * @remarks Обратите внимание, что если значение json является числом, но представлено как double,
     * его все равно можно получить как целое число с помощью as_integer (), однако значение будет усечено.
     * @return false если не представлено
     */
    bool is_integer() const;

    /**
     * @brief Представлено ли текущее значение как double?
     * @remarks Обратите внимание, что если значение json является числом, но представлено как int,
     * его все равно можно получить как double с помощью as_double ().
     * @return false если не представлено
     */
    bool is_double() const;

    /**
     * @brief Текущее значение является строковым значением?
     * @return false если не является
     */
    bool is_string() const;

    /**
     * @brief Текущее значение является массивом?
     * @return false если не является
     */
    bool is_array() const;

    /**
     * @brief Текущее значение является объектом?
     * @return false если не является
     */
    bool is_object() const;

    /**
     * @brief Возвращает количество дочерних объектов.
     * @return Количество дочерних объектов. 0 для всех не композитных
     */
    size_t size() const;

    /**
     * @brief Выполняет парсинг строки и конструирует JSON-значение.
     * @param value Значение C++ из которого создается JSON-значение
     */
    static value parse(const std::string& value);

    /**
     * @brief Выполняет сериализацию текущего JSON-значения в C++ строку
     * @return Представление значения в виде строки
     */
    std::string serialize() const;

    /**
     * @brief Конвертирует JSON-значение в C++ double.
     * @throw json_exception если JSON-значение не является типом "Number"
     * @return Представление значения в виде double
     */
    double as_double() const;

    /**
     * @brief Конвертирует JSON-значение в C++ int.
     * @throw json_exception если JSON-значение не является типом "Number"
     * @return Представление значения в виде целого числа
     */
    int as_integer() const;

    /**
     * @brief Конвертирует JSON-значение в JSON-массив
     * @throw json_exception если JSON-значение не является типом "Array"
     * @remarks Возвращенный json::array должен иметь такое же или меньшее время жизни, как this
     * @return Представление значение в виде массива
     */
    json::array& as_array();

    /**
     * @brief Конвертирует JSON-значение в JSON-массив
     * @throw json_exception если JSON-значение не является типом "Array"
     * @remarks Возвращенный json::array должен иметь такое же или меньшее время жизни, как this
     * @return Представление значение в виде массива
     */
    const json::array& as_array() const;

    /**
     * @brief Конвертирует JSON-значение в C++ строку.
     * @throw json_exception если JSON-значение не является типом "String"
     * @remarks Возвращенный std::string должен иметь такое же или меньшее время жизни, как this
     * @return Представление значения в виде строки
     */
    const std::string& as_string() const;

    /**
     * @brief Предоставляет доступ к элементу JSON-объекта.
     * @param key ключ по которому производится поиск элемента
     * @throw json_exception если не найдено
     * @remarks Возвращенный json::value должен иметь такое же или меньшее время жизни, как this
     * @return Ссылка на элемент
     */
    const json::value& at(const std::string& key) const;

    /**
     * @brief Предоставляет доступ к полю JSON-объекта
     * @param key имя искомого поля
     * @throw json_exception если JSON-значение не является типом "Object"
     * @remarks Возвращенный json::value должен иметь такое же или меньшее время жизни, как this
     * @return Ссылка на элемент
     */
    json::value& operator[](const std::string& key);

private:
    std::optional<std::variant<int, double, std::string, json::array, json::object>> m_value;
};

inline array::iterator array::begin() { return m_elements.begin(); }

inline array::const_iterator array::begin() const { return m_elements.cbegin(); }

inline array::iterator array::end() { return m_elements.end(); }

inline array::const_iterator array::end() const { return m_elements.cend(); }

inline array::size_type array::size() const { return m_elements.size(); }

inline value& array::at(array::size_type index)
{
    return const_cast<json::value&>(static_cast<const array&>(*this).at(index));
}

inline const value& array::at(array::size_type index) const
{
    if (index >= m_elements.size())
        throw json_exception("index out of bounds");

    return m_elements[index];
}

inline object::iterator object::begin() { return m_elements.begin(); }

inline object::const_iterator object::begin() const { return m_elements.cbegin(); }

inline object::iterator object::end() { return m_elements.end(); }

inline object::const_iterator object::end() const { return m_elements.cend(); }

inline object::size_type object::size() const { return m_elements.size(); }

inline const value& object::at(const std::string& key) const
{
    auto it = m_elements.find(key);
    if (m_elements.end() == it)
        throw json::json_exception("Key not found");
    return it->second;
}

inline value& object::operator[](const std::string& key)
{
    return m_elements[key];
}

inline object::const_iterator object::find(const std::string& key) const
{
    return m_elements.find(key);
}

inline value value::null()
{
    return value {};
}

inline value value::number(double _value)
{
    return value { std::move(_value) };
}

inline value value::number(int _value)
{
    return value { std::move(_value) };
}

inline value value::string(std::string _value)
{
    return value { std::move(_value) };
}

inline value value::array()
{
    return callInitializer([](value& _) { _.m_value = json::array {}; });
}

inline value value::array(size_t size)
{
    return callInitializer([&](value& _) { _.m_value = json::array { size }; });
}

inline value value::object()
{
    return callInitializer([](value& _) { _.m_value = json::object {}; });
}

inline bool value::has_field(const std::string& key) const
{
    bool has = false;
    std::visit(overloaded { [](const auto&) {},
                   [&](const json::object& value) {
                       has = (value.find(key) != value.end());
                   } },
        m_value.value_or(json::object {}));
    return has;
}

inline value::value_type value::type() const
{
    value_type type = Null;
    if (m_value.has_value()) {
        std::visit(overloaded {
                       [&](int) {
                           type = Number;
                       },
                       [&](double) {
                           type = Number;
                       },
                       [&](const std::string&) {
                           type = String;
                       },
                       [&](const json::array&) {
                           type = Array;
                       },
                       [&](const json::object&) {
                           type = Object;
                       } },
            m_value.value());
    }
    return type;
}

inline bool value::is_number() const { return type() == Number; }

inline bool value::is_integer() const
{
    bool is = false;
    if (m_value.has_value()) {
        std::visit(overloaded {
                       [](const auto&) {},
                       [&](int) {
                           is = true;
                       } },
            m_value.value());
    }
    return is;
}

inline bool value::is_double() const
{
    bool is = false;
    if (m_value.has_value()) {
        std::visit(overloaded {
                       [](const auto&) {},
                       [&](double) {
                           is = true;
                       } },
            m_value.value());
    }
    return is;
}

inline bool value::is_string() const { return type() == String; }

inline bool value::is_array() const { return type() == Array; }

inline bool value::is_object() const { return type() == Object; }

inline size_t value::size() const
{
    size_t ret = 0;
    std::visit(overloaded {
                   [](const auto&) {},
                   [&](const json::array& arg) {
                       ret = arg.size();
                   },
                   [&](const json::object& arg) {
                       ret = arg.size();
                   } },
        m_value.value_or(json::array {}));
    return ret;
}

inline double value::as_double() const
{
    auto ret = std::optional<double> {};
    if (m_value.has_value()) {
        std::visit(overloaded {
                       [](const auto&) {},
                       [&](int arg) {
                           ret = static_cast<double>(arg);
                       },
                       [&](double arg) {
                           ret = arg;
                       } },
            m_value.value());
    }

    if (!ret.has_value())
        throw json_exception("not a number");

    return ret.value();
}

inline int value::as_integer() const
{
    auto ret = std::optional<int> {};
    if (m_value.has_value()) {
        std::visit(overloaded {
                       [](const auto&) {},
                       [&](int arg) {
                           ret = arg;
                       },
                       [&](double arg) {
                           ret = static_cast<int>(arg);
                       } },
            m_value.value());
    }

    if (!ret.has_value())
        throw json_exception("not a number");

    return ret.value();
}

inline array& value::as_array()
{
    return const_cast<json::array&>(static_cast<const value&>(*this).as_array());
}

inline const array& value::as_array() const
{
    auto ret = std::optional<std::reference_wrapper<const json::array>> {};

    if (m_value.has_value()) {
        std::visit(overloaded {
                       [](const auto&) {},
                       [&](const json::array& arg) {
                           ret = arg;
                       } },
            m_value.value());
    }

    if (!ret.has_value())
        throw json_exception("not an array");

    return ret.value();
}

inline const std::string& value::as_string() const
{
    auto ret = std::optional<std::reference_wrapper<const std::string>> {};

    if (m_value.has_value()) {
        std::visit(overloaded {
                       [](const auto&) {},
                       [&](const std::string& arg) {
                           ret = arg;
                       } },
            m_value.value());
    }

    if (!ret.has_value())
        throw json_exception("not a string");

    return ret.value();
}

inline const value& value::at(const std::string& key) const
{
    auto ret = std::optional<std::reference_wrapper<const json::value>> {};

    if (m_value.has_value()) {
        std::visit(overloaded {
                       [](const auto&) {},
                       [&](const json::object& arg) {
                           ret = arg.at(key);
                       } },
            m_value.value());
    }

    if (!ret.has_value())
        throw json_exception("Key not found");

    return ret.value();
}

inline value& value::operator[](const std::string& key)
{
    auto ret = std::optional<std::reference_wrapper<json::value>> {};

    if (m_value.has_value()) {
        std::visit(overloaded {
                       [](auto&) {},
                       [&](json::object& arg) {
                           ret = arg[key];
                       } },
            m_value.value());
    }

    if (!ret.has_value())
        throw json_exception("Key not found");

    return ret.value();
}
} // end of namespace json

#endif // INC_VALUE_HPP
