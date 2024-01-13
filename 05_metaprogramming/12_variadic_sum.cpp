#include <iostream>
#include <typeinfo>

template <typename T>
inline T sum(T t) { return t; }

#define VERSION 2
#if VERSION == 0

template <typename T, typename ...P>
T sum(T t, P ...p) { return t + sum(p...); }

#elif VERSION == 1

template <typename T, typename ...P>
auto sum(T t, P ...p) -> decltype( t + sum(p...) ) { return t + sum(p...); }

#elif VERSION == 2

template <typename ...P> struct sum_type;

template <typename T, typename ...P>
struct sum_type<T, P...> { typedef decltype(T() + typename sum_type<P...>::type()) type; };

template <typename T>
struct sum_type<T> { typedef T type; };

template <typename ...P>
using sum_type_t = typename sum_type<P...>::type;

template <typename T, typename... P>
// typename std::common_type<T, P...>::type
inline sum_type_t<T, P...> sum(T t, P... p)
{
    return t + sum(p...);
}

#endif


int main()
{
    auto s = sum(-7, 3.7f, 9u, -2.6);
    std::cout << "s is " << s << " and its type is " << typeid(s).name() << '\n';

    auto s2 = sum(-7, 3.7f, 9u, -42.6);
    std::cout << "s2 is " << s2 << " and its type is " << typeid(s2).name() << '\n';

    return 0;
}