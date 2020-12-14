#ifndef TREE_H
#define TREE_H

#include <string>
#include <variant>
#include <vector>

namespace json {
class value;
} // end of namespace json

/**
 * @class tree_exception
 */
class tree_exception : public std::exception {
private:
    std::string _message;

public:
    tree_exception(const char* const message)
        : _message(message)
    {
    }
    tree_exception(std::string&& message)
        : _message(std::move(message))
    {
    }

    const char* what() const noexcept { return _message.c_str(); }
};

/**
 * @class tree
 * @brief Дерево, в узлах которого могут храниться данные трёх типов
 */
class tree {
public:
    /**
     * @brief Конструирует дерево с целочисленным значением в корневом элементе
     * @param value целочисленное значение
     * @param childs дочерние элементы дерева
     */
    explicit tree(int value, std::vector<tree> childs = {}) noexcept;

    /**
     * @brief Конструирует дерево с числом с плавающей точкой двойной точности в корневом элементе
     * @param value число с плавающей точкой двойной точности
     * @param childs дочерние элементы дерева
     */
    explicit tree(double value, std::vector<tree> childs = {}) noexcept;

    /**
     * @brief Конструирует дерево со строкой в корневом элементе
     * @param value строка
     * @param childs дочерние элементы дерева
     */
    explicit tree(std::string value, std::vector<tree> childs = {}) noexcept;

    /**
     * @brief Хранит ли корневой узел целочисленное значение?
     * @return false если не хранит
     */
    bool isInteger() const noexcept;

    /**
     * @brief Хранит ли корневой узел число с плавающей точкой двойной точности?
     * @return false если не хранит
     */
    bool isDouble() const noexcept;

    /**
     * @brief Хранит ли корневой узел строку?
     * @return false если не хранит
     */
    bool isString() const noexcept;

    /**
     * @brief Возвращает хранимое в корневом узле целочисленное значение
     * @throw std::bad_variant_access если узел хранит значение другого типа
     * @return целочисленное значение
     */
    int asInteger() const;

    /**
     * @brief Возвращает хранимое в корневом узле число с плавающей точкой двойной точности
     * @throw std::bad_variant_access если узел хранит значение другого типа
     * @return число с плавающей точкой двойной точности
     */
    double asDouble() const;

    /**
     * @brief Возвращает хранимую в корневом узле строку
     * @throw std::bad_variant_access если узел хранит значение другого типа
     * @return строка
     */
    std::string asString() const;

    /**
     * @brief выполняет парсинг JSON-значения в дерево.
     * @param root JSON-значение
     * @throw tree_exception если парсинг не удался
     * @return Созданный из парсинга JSON-значения экземпляр
     */
    static tree parse(const json::value& root);

    /**
     * @brief Выполняет сериализацию дерева в JSON-значение
     * @return JSON-значение
     */
    json::value serialize() const;

    /**
     * @brief Возвращает ссылку на контейнер дочерних элементов дерева
     * @return ссылка на контейнер дочерних элементов
     */
    std::vector<tree>& childs() noexcept;

    /**
     * @brief Возвращает ссылку на контейнер дочерних элементов дерева
     * @return ссылка на контейнер дочерних элементов
     */
    const std::vector<tree>& childs() const noexcept;

private:
    static inline const std::string NODE_FN = "node";
    static inline const std::string SUBNODES_FN = "subnodes";

    std::variant<std::string, int, double> m_node;
    std::vector<tree> m_subnodes;
};

inline bool tree::isInteger() const noexcept
{
    return !!(std::get_if<int>(&m_node));
}

inline bool tree::isDouble() const noexcept
{
    return !!(std::get_if<double>(&m_node));
}

inline bool tree::isString() const noexcept
{
    return !!(std::get_if<std::string>(&m_node));
}

inline int tree::asInteger() const
{
    return std::get<int>(m_node);
}

inline double tree::asDouble() const
{
    return std::get<double>(m_node);
}

inline std::string tree::asString() const
{
    return std::get<std::string>(m_node);
}

inline std::vector<tree>& tree::childs() noexcept
{
    return m_subnodes;
}

inline const std::vector<tree>& tree::childs() const noexcept
{
    return m_subnodes;
}

#endif // TREE_H
