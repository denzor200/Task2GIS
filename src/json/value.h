#ifndef INC_VALUE_HPP
#define INC_VALUE_HPP

#include "ast/value.hpp"

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

    /**
     * @brief Конструктор, создающий значение типа "Null"
     */
    value() = default;

    /**
     * @brief Конструктор, создающий значение типа "Number"
     * @param value Значение C++ из которого создается JSON-значение
     */
    value(int32_t value);

    /**
     * @brief Конструктор, создающий значение типа "Number"
     * @param value Значение C++ из которого создается JSON-значение
     */
    value(uint32_t value);

    /**
     * @brief Конструктор, создающий значение типа "Number"
     * @param value Значение C++ из которого создается JSON-значение
     */
    value(int64_t value);

    /**
     * @brief Конструктор, создающий значение типа "Number"
     * @param value Значение C++ из которого создается JSON-значение
     */
    value(uint64_t value);

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
    value(const value&);

    /**
     * @brief Перемещающий конструктор
     */
    value(value&&) noexcept;

    /**
     * @brief Оператор присваивания
     * @returns JSON-значение, содержащее результат присваивания
     */
    value& operator=(const value&);

    /**
     * @brief Оператор присваивания перемещением
     * @returns JSON-значение, содержащее результат присваивания
     */
    value& operator=(value&&) noexcept;

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
    static value number(int32_t value);

    /**
     * @brief Создает значение типа "number"
     * @param value Значение C++ из которого создается JSON-значение
     * @return JSON-значение типа "number"
     */
    static value number(uint32_t value);

    /**
     * @brief Создает значение типа "number"
     * @param value Значение C++ из которого создается JSON-значение
     * @return JSON-значение типа "number"
     */
    static value number(int64_t value);

    /**
     * @brief Создает значение типа "number"
     * @param value Значение C++ из которого создается JSON-значение
     * @return JSON-значение типа "number"
     */
    static value number(uint64_t value);

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
     * @brief Проверяет на наличие поля
     * @param key имя поля
     * @return false если поле не найдено
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
    const json::array& as_array() const;

    /**
     * @brief Конвертирует JSON-значение в C++ строку.
     * @throw json_exception если JSON-значение не является типом "String"
     * @return Представление значения в виде строки
     */
    const std::string& as_string() const;

    /**
     * @brief Предоставляет доступ к элементу JSON-массива.
     * @param index позиция элемента в массиве
     * @throw json_exception если index выходит за предел
     * @return Ссылка на элемент
     */
    json::value& at(size_t index);

    /**
     * @brief Предоставляет доступ к элементу JSON-массива.
     * @param index позиция элемента в массиве
     * @throw json_exception если index выходит за предел
     * @return Ссылка на элемент
     */
    const json::value& at(size_t index) const;

    /**
     * @brief Предоставляет доступ к элементу JSON-объекта.
     * @param key ключ по которому производится поиск элементы
     * @throw json_exception если не найдено
     * @return Ссылка на элемент
     */
    json::value& at(const std::string& key);

    /**
     * @brief Предоставляет доступ к элементу JSON-объекта.
     * @param key ключ по которому производится поиск элементы
     * @throw json_exception если не найдено
     * @return Ссылка на элемент
     */
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
    array(storage_type elements);

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
