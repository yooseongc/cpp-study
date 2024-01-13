#include <iostream>
#include <cmath>
#include <vector>
#include <complex>

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

template <typename T>
struct Magnitude<std::vector<T> >
{
    using type = typename Magnitude<T>::type;
};

template <typename T>
T inline min_magnitude(const T& x, const T& y)
{
    using std::abs;
    typename Magnitude<T>::type ax = abs(x), ay = abs(y);
    return ax < ay ? x : y;
}

int main()
{
    using namespace std;
    
    double d1 = 3., d2 = 4.;
    cout << "min |d1, d2| = " << min_magnitude(d1, d2) << endl;

    std::complex<double> c1(3.), c2(4.);
    cout << "min |c1, c2| = " << min_magnitude(c1, c2) << endl;

    return 0;
}
