#pragma once

namespace app
{
template <typename T, typename... Ts>
struct is_any_of : std::bool_constant<(std::is_same_v<T, Ts> || ...)>
{
};

template <typename T, typename T1, typename... Ts>
inline constexpr bool is_any_of_v = is_any_of<T, T1, Ts...>::value;

}  // namespace app
