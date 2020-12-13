#ifndef TREE_H
#define TREE_H

#include <string>
#include <variant>
#include <vector>

// TODO: docs

namespace json {
class value;
} // end of namespace json

class tree {
public:
    explicit tree(int value, std::vector<tree> childs = {}) noexcept;

    explicit tree(double value, std::vector<tree> childs = {}) noexcept;

    explicit tree(std::string value, std::vector<tree> childs = {}) noexcept;

    bool isInteger() const noexcept;

    bool isDouble() const noexcept;

    bool isString() const noexcept;

    int asInteger() const;

    double asDouble() const;

    std::string asString() const;

    static tree parse(const json::value& root);

    json::value serialize() const;

    std::vector<tree>& childs() noexcept;

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
