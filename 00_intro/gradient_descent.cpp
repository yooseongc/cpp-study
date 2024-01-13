
#include <valarray>

void gradient_descent(
    double* x,
    double* y,
    double s,
    double eps,
    double(*f)(double, double),
    double(*gx)(double, double),
    double(*gy)(double, double)
)
{
    double val = f(*x, *y), delta;
    do
    {
        *x -= s * gx(*x, *y);
        *y -= s * gy(*x, *y);
        double new_val = f(*x, *y);
        delta = abs(new_val - val);
        val = new_val;
    }
    while (delta > eps);
}
