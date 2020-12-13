#ifndef UTILS_H
#define UTILS_H

#include <boost/callable_traits.hpp>
#include <functional>
#include <tuple>

/// Хэлпер для шаблонного вызова std::visit
/// https://en.cppreference.com/w/cpp/utility/variant/visit
template <class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

/// Хэлпер для шаблонного вызова std::visit
/// https://en.cppreference.com/w/cpp/utility/variant/visit
template <class... Ts>
overloaded(Ts...)->overloaded<Ts...>;

/**
 * @brief  Выполняет функциональный объект, предназначенный для инициализации некоторой структуры
 * Возвращает проинициализированную структуру
 * @param proc функциональный объект
 */
template <typename TProc>
inline auto callInitializer(const TProc& proc)
{
    namespace ct = boost::callable_traits;

    static_assert((std::tuple_size_v<ct::args_t<TProc>> == 1),
        "You must pass some function object to callInitializer that takes only one argument");

    using TFirst = std::tuple_element_t<0, ct::args_t<TProc>>;
    using TStruct = std::decay_t<TFirst>;

    static_assert((std::is_reference_v<TFirst>),
        "You must pass some functional object to callInitializer that only accepts a reference");

    auto s = TStruct {};
    proc(std::ref(s));
    return s;
}

#endif // UTILS_H
