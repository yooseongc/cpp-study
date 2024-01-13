
#include <valarray>

template <typename Value, typename P1, typename P2, typename F, typename G>
Value gradient_descent(Value x, P1 s, P2 eps, F f, G g)
{
    auto val = f(x), delta = val;
    do
    {
        *x -= s * g(x);
        auto new_val = f(x);
        delta = abs(new_val - val);
        val = new_val;
    } 
    while (delta > eps);
    return x;
}
