#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

constexpr long fibonacci(long n)
{
    return n <= 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);
}

template <typename T>
constexpr T square(const T& x)
{
    return x * x;
}

#if defined(__GNUC__) && __GNUC__ == 4 && __GNUC_MINOR__ >= 7 && __GNUC_MINOR__ <= 9
constexpr long floor_sqrt(long n)
{
    return floor(sqrt(n));
}
#endif

template <long N>
struct static_long
{
    static const long value = N;
};

int main(int argc, char* argv[])
{
    cout << "fibonacci(7) = " << fibonacci(7) << endl;
    static_long<fibonacci(7)> fibo7;

    if(argc > 1)
    {
        long n2 = atoi(argv[1]);
        cout << "fibonacci(" << n2 << ") = " << fibonacci(n2) << endl;
    }

#if defined(__GNUC__) && __GNUC__ == 4 && __GNUC_MINOR__ >= 7 && __GNUC_MINOR__ <= 9
    cout << "floor_sqrt(17) = " << floor_sqrt(17) << endl;
    static_long<floor_sqrt(17)> sfs;
#endif

    constexpr double x = square(3.7);

    return 0;
}
