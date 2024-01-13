#include <iostream>
#include <cmath>
#include <complex>
#include <type_traits>

#ifndef MTL_WITH_INITLIST
#define MTL_WITH_INITLIST
#endif
#ifndef MTL_WITH_AUTO
#define MTL_WITH_AUTO
#endif
#ifndef MTL_WITH_RANGEDFOR
#define MTL_WITH_RANGEDFOR
#endif

#include <boost/numeric/mtl/mtl.hpp>

namespace tst
{
    template <typename T>
    struct is_matrix
        : std::false_type
    {};

    template <typename Value, typename Para>
    struct is_matrix<mtl::dense2D<Value, Para> >
        : std::true_type
    {};

    template <typename T>
    struct is_vector
        : std::false_type
    {};

    template <typename Value, typename Para>
    struct is_vector<mtl::dense_vector<Value, Para> >
        : std::true_type
    {};

    template <typename T>
    struct Magnitude
    {
        using type = T;
    };

    template <typename T>
    struct Magnitude<std::complex<T> >
    {
        using type = T;
    };

    template <typename T, typename Para>
    struct Magnitude<mtl::dense_vector<T, Para> >
    {
        using type = typename Magnitude<T>::type;
    };

    template <typename T, typename Para>
    struct Magnitude<mtl::dense2D<T, Para> >
    {
        using type = typename Magnitude<T>::type;
    };

    template <typename T>
    using Magnitude_t = typename Magnitude<T>::type;

    template <bool Condition, typename T = void>
    struct enable_if
    {
        using type = T;
    };

    template <typename T>
    struct enable_if<false, T> {};

    template <bool Condition, typename T = void>
    using enable_if_t = typename enable_if<Condition, T>::type;

    template <typename T>
    enable_if_t<is_matrix<T>::value, Magnitude_t<T> >
    inline one_norm(const T& A)
    {
        using std::abs;
        Magnitude_t<T> max{0};
        for(unsigned c = 0; c < num_cols(A); c++)
        {
            Magnitude_t<T> sum{0};
            for(unsigned r = 0; r < num_rows(A); r++)
            {
                sum += abs(A[r][c]);
            }
            max = (max < sum) ? sum : max;
        }
        return max;
    }

    template <typename T>
    enable_if_t<is_vector<T>::value, Magnitude_t<T> >
    inline one_norm(const T& v)
    {
        using std::abs;
        Magnitude_t<T> sum{0};
        for(unsigned r = 0; r < size(v); r++)
        {
            sum += abs(v[r]);
        }
        return sum;
    }

}

int main()
{
    mtl::dense2D<float> A = {{2, 3, 4},
                             {5, 6, 7},
                             {8, 9, 10}};
    mtl::dense_vector<float> v{3, 4, 5};

    std::cout << "one_norm(A) is " << tst::one_norm(A) << std::endl;
    std::cout << "one_norm(v) is " << tst::one_norm(v) << std::endl;

    return 0;
}
