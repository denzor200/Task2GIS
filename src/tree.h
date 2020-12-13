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

    bool is_integer() const noexcept;

    bool is_double() const noexcept;

    bool is_string() const noexcept;

    int as_integer() const;

    double as_double() const;

    std::string as_string() const;

    static tree parse(const json::value& root);

    json::value serialize() const;

    std::vector<tree>& childs() noexcept;

    const std::vector<tree>& childs() const noexcept;

private:
    static inline const std::string VALUE_FN = "value"; // TODO: rename to node
    static inline const std::string CHILDS_FN = "childs"; // TODO: rename to subnodes

    std::variant<std::string, int, double> m_value;
    std::vector<tree> m_childs;
};

inline bool tree::is_integer() const noexcept
{
    return !!(std::get_if<int>(&m_value));
}

inline bool tree::is_double() const noexcept
{
    return !!(std::get_if<double>(&m_value));
}

inline bool tree::is_string() const noexcept
{
    return !!(std::get_if<std::string>(&m_value));
}

inline int tree::as_integer() const
{
    return std::get<int>(m_value);
}

inline double tree::as_double() const
{
    return std::get<double>(m_value);
}

inline std::string tree::as_string() const
{
    return std::get<std::string>(m_value);
}

inline std::vector<tree>& tree::childs() noexcept
{
    return m_childs;
}

inline const std::vector<tree>& tree::childs() const noexcept
{
    return m_childs;
}

#endif // TREE_H
