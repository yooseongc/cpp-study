export module math;
export import math.extra;

namespace math
{
    export bool is_prime(long i);

    auto square(auto x) { return x * x; }

    export auto cubic(auto x) { return square(x) * x; }

    #define MACRO_SQUARE(x) ((x) * (x))
}
