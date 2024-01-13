#include <iostream>

using namespace std;

namespace dmc
{
    consteval long fibonacci(long n)
    {
        return n <= 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main()
{
    constexpr long fibo8 = dmc::fibonacci(8);
    
    // long var = 9;
    // dmc::fibonacci(var);

    dmc::fibonacci(fibo8);

    return 0;
}
