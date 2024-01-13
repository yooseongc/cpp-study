#include <iostream>
#include <cstddef>
#include <cassert>

using namespace std;

constexpr size_t popcount_recursive(size_t x)
{
    return x == 0 ? 0 : popcount_recursive(x & x - 1) + 1;
}

constexpr size_t popcount(size_t x)
{
    size_t count = 0;
    for(; x != 0; ++count)
    {
        x &= x - 1;
    }
    return count;
}

int main()
{
    constexpr size_t bits = popcount(0x5555);
    static_assert(popcount(0x5555) == 8, "popcount(0x5555) != 8");
    constexpr size_t bits2 = popcount_recursive(0x5555);
    static_assert(popcount_recursive(0x5555) == 8, "popcount_recursive(0x5555) != 8");
    return 0;
}
