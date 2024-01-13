#include <iostream>
#include <algorithm>
#include <typeinfo>
#include <type_traits>

template <typename T>
inline T minimum(const T& t) { return t; }

template <typename T, typename ...P>
auto minimum(const T& t, const P& ...p)
{
    using res_type = std::common_type_t<T, P...>;
    return std::min(res_type(t), res_type(minimum(p...)));
}

int main()
{
    auto m = minimum(-7, 3.7f, 9u, -2.6);
    std::cout << "m is " << m << " and its type is " << typeid(m).name() << '\n';

    auto m2 = minimum(-7, 3.7f, 9u, -42.6);
    std::cout << "m2 is " << m2 << " and its type is " << typeid(m2).name() << '\n';

    return 0;
}
