#ifndef GENERATOR_H
#define GENERATOR_H

#include <sstream>

namespace json {
class value;
} // end of namespace json

namespace detail {

/**
 * @class generator
 * @brief Генератор строк из JSON-значения
 */
class generator {
    std::stringstream m_ss;

    const json::value* m_value;
    unsigned m_level;

public:
    /**
     * @brief Конструирует генератор для конкретного JSON-значения
     * @param value ссылка на JSON-значение
     * @warning время жизни генератора не должно превышать
     * время жизни значения, на которое ссылается value
     */
    generator(const json::value& value);

    /**
     * @brief Выполняет рекурсивную генерации строки,
     * сохраняет результат во внутреннем состоянии объекта
     */
    void generate();

    /**
     * @brief Получить результат генерации
     * @return строка, идентичная JSON-значению
     */
    std::string string() const;

private:
    /**
     * @brief Выполняет рекурсивную генерации строки,
     * опуская предварительную печать пробелов непосредственно перед печатью значения
     */
    void generate2nd();

    /**
     * @brief Выполняет рекурсивную генерации строки,
     * зная что текущее JSON-значение является "Null"
     */
    void generateNull();

    /**
     * @brief Выполняет рекурсивную генерации строки,
     * зная что текущее JSON-значение является "Number"
     */
    void generateNumber();

    /**
     * @brief Выполняет рекурсивную генерации строки,
     * зная что текущее JSON-значение является "String"
     */
    void generateString();

    /**
     * @brief Выполняет рекурсивную генерации строки,
     * зная что текущее JSON-значение является "Array"
     */
    void generateArray();

    /**
     * @brief Выполняет рекурсивную генерации строки,
     * зная что текущее JSON-значение является "Object"
     */
    void generateObject();

    /**
     * @brief Присвоить JSON-значение к рассмотрению, установить глубину рекурсии.
     * @param value ссылка на JSON-значение
     * @param level глубина рекурсии
     */
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
