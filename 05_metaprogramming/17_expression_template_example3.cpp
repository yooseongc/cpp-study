#include <cassert>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>
#include <initializer_list>
#include <algorithm>

template <typename T>
using copy_or_cref = std::conditional_t<
    std::is_lvalue_reference_v<T>,
    std::remove_reference_t<T> const&,
    std::remove_reference_t<T>
>;

template <typename T>
class vector
{
    public:
        void check_size(int that_size) const { assert(my_size == that_size); }
        void check_index(int i) const { assert( i >= 0 && i < my_size ); }

        explicit vector(int size) : my_size{size}, data{new T[my_size]} {}
        vector() : my_size{0}, data{nullptr} {}
        vector(const vector &that) : my_size{size(that)}, data{new T[my_size]}
        {
            for(int i = 0; i < my_size; ++i) data[i] = that.data[i];
        }
        vector(std::initializer_list<T> values) : my_size(values.size()), data{new T[my_size]}
        {
            std::copy(values.begin(), values.end(), data.get());
        }

        template <typename Src>
        vector& operator=(const Src& that)
        {
            check_size(size(that));
            for(int i = 0; i < my_size; ++i) data[i] = that[i];
            return *this;
        }

        friend int size(const vector& x) { return x.my_size; }

        const T& operator[](int i) const { check_index(i); return data[i]; }
        T& operator[](int i) { check_index(i); return data[i]; }
    
    private:
        int                     my_size;
        std::unique_ptr<T[]>    data;
};

template <typename Value>
std::ostream& operator<<(std::ostream & os, const vector<Value> &v)
{
    os << '[';
    if (size(v) > 0)
        os << v[0];
    for (int i = 1; i < size(v); os << ", " << v[i], ++i)
        ;
    return os << ']';
}

template <typename V1, typename V2>
class vector_sum
{
    void check_index(int i) const { assert(i >= 0 && i < size(v1)); }
    public:
        vector_sum(V1 v1, V2 v2) : v1{v1}, v2{v2}
        {
            assert(size(v1) == size(v2));
        }

        friend int size(const vector_sum &x)
        {
            return size(x.v1);
        }

        decltype(auto) operator[](int i) const { check_index(i); return v1[i] + v2[i]; }

    private:
        V1 v1;
        V2 v2;
};

// 1. using deduction guide
template <typename VV1, typename VV2>
vector_sum(VV1 &&, VV2 &&) -> vector_sum<copy_or_cref<VV1>, copy_or_cref<VV2>>;

template <typename V1, typename V2>
auto inline operator+(V1&& x, V2&& y) 
{ 
    return vector_sum{ std::forward<V1>(x), std::forward<V2>(y) }; 
}

// 2. using operator type deduction
// template <typename V1, typename V2>
// auto inline operator+(V1&& x, V2&& y) -> vector_sum<copy_or_cref<V1>, copy_or_cref<V2>>
// {
//     return { x, y };
// }

template <typename V1, typename V2>
std::ostream &operator<<(std::ostream &os, const vector_sum<V1, V2>& v)
{
    os << '[';
    if (size(v) > 0)
        os << v[0];
    for (int i = 1; i < size(v); os << ", " << v[i], ++i)
        ;
    return os << ']';
}

int main()
{
    vector<float> x(4), y(4), z(4), w(4);
    x[0] = x[1] = 1.0;
    x[2] = 2.0;
    x[3] = -3.0;
    y[0] = y[1] = 1.7;
    y[2] = 4.0;
    y[3] = -6.0;
    z[0] = z[1] = 4.1;
    z[2] = 2.6;
    z[3] = 11.0;

    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;
    std::cout << "z = " << z << std::endl;

    for(int i = 0; i < 2000; ++i)
    {
        x + y + z + vector{2.0, 8.4, 9.1, 11.1} + vector{i, 2, 3, 4} + vector { i, 2, 3, 4 };
        if(i % 100 == 0) std::cout << ".";
    }

    std::cout << std::endl;

    std::cout << (x + y + z + vector{2.0, 8.4, 9.1, 11.1} + vector{1, 2, 3, 4} + vector{1, 2, 3, 4}) << std::endl;
    w = x + y + (z + vector{2.0, 8.4, 9.1, 11.1}) + vector{1, 2, 3, 4} + vector{1, 2, 3, 4};
    std::cout << "w = " << w << std::endl;

    std::cout << typeid(x + y + z + vector{2.0, 8.4, 9.1, 11.1}).name() << std::endl;

    return 0;
}
