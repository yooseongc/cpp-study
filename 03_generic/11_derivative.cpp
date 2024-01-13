#include <cmath>
#include <iostream>
#include <boost/mpl/bool.hpp>
#include <boost/lambda/lambda.hpp>

double sc(double x)
{
    return sin(x) + cos(x);
}

struct sc_f
{
    double operator()(double x) const
    {
        return sin(x) + cos(x);
    }
};

class psc_f
{
    public:
        psc_f(double alpha) : alpha(alpha) {}
        
        double operator()(double x) const
        {
            return sin(alpha * x) + cos(x);
        }
    
    private:
        double alpha;
};

#if 0

// with function pointers
double fin_diff(double f(double), double x, double h)
{
    return ( f(x + h) - f(x) ) / h;
}

#endif

template <typename F, typename T>
inline T fin_diff(F f, const T& x, const T& h)
{
    return ( f(x + h) - f(x) ) / h;
}

template <typename F, typename T>
class derivative
{
    public:
        derivative(const F& f, const T& h) : f(f), h(h) {}

        T operator()(const T& x) const
        {
            return ( f(x + h) - f(x) ) / h;
        }

    private:
        const F& f;
        T h;
};

template <typename F, typename T>
class second_derivative
{
    public:
        second_derivative(const F& f, const T& h) : h(h), fp(f, h) {}

        T operator()(const T& x) const
        {
            return ( fp(x + h) - fp(x) ) / h;
        }

    private:
        T h;
        derivative<F, T> fp;
};

#if 0

template <unsigned N, typename F, typename T>
class nth_derivative
{
        using prev_derivative= nth_derivative<N-1, F, T>;
    
    public:
        nth_derivative(const F& f, const T& h) : h(h), fp(f, h) {}

        T operator()(const T& x) const
        {
            return ( fp(x + h) - fp(x) ) / h;
        }

    private:
        T h;
        prev_derivative fp;

};

#else

template <unsigned N, typename F, typename T>
class nth_derivative
{
    using prev_derivative = nth_derivative<N - 1, F, T>;

public:
    nth_derivative(const F& f, const T& h) : h(h), fp(f, h) {}

    T operator()(const T &x) const
    {
        return N & 1 ? (fp(x + h) - fp(x)) / h
                     : (fp(x) - fp(x - h)) / h;
    }

private:
    T h;
    prev_derivative fp;
};

#endif

#if 0
template <typename F, typename T>
class nth_derivative<1, F, T>
{
  public:
    nth_derivative(const F& f, const T& h) : f(f), h(h) {}

    T operator()(const T& x) const
    {
	    return ( f(x+h) - f(x) ) / h;
    }   

  private:
    const F& f;
    T        h;
};
#endif

template <typename F, typename T>
class nth_derivative<1, F, T>
    : public derivative<F, T>
{
    using derivative<F, T>::derivative;  // inherit constructors of derivative<F, T>

    // public:
    //   nth_derivative(const F& f, const T& h) : derivative<F, T>(f, h) {}
};

#if 0

template <typename F, typename T, unsigned N> // Not Clear
nth_derivative<N, F, T>
derive(const F& f, const T& h)
{
    return nth_derivative<N, F, T>(f, h);
}

#endif

template <unsigned N, typename F, typename T>
nth_derivative<N, F, T>
derive(const F& f, const T& h= 0.0001)
{
    return nth_derivative<N, F, T>(f, h);
}

struct et {};

template <typename F>
void error(const F& f)
{
    et e= f;
}

int main()
{
    using namespace std;

    cout << fin_diff(sc, 1., 0.001) << '\n';
    cout << fin_diff(sc, 0., 0.001) << '\n';

    psc_f psc_o(1.0);
    cout << fin_diff(psc_o, 1., 0.001) << endl;
    cout << fin_diff(psc_f(2.0), 1., 0.001) << endl;
    cout << fin_diff(psc_f(2.0), 0., 0.001) << endl;
    cout << fin_diff(sc_f(), 0., 0.001) << endl;

    using d_psc_f= derivative<psc_f, double>;
    using dd_psc_f= derivative<d_psc_f, double>;

    d_psc_f d_psc_o(psc_o, 0.001);
    dd_psc_f dd_psc_o(d_psc_o, 0.001);

    cout << "derivative of sin(0) + cos(0) is " << d_psc_o(0.0) << '\n';
    cout << "2nd derivative of sin(0) + cos(0) is " << dd_psc_o(0.0) << '\n';

    second_derivative<psc_f, double> dd_psc_2_o(psc_f(1.0), 0.001);
    cout << "2nd derivative of sin(0) + cos(0) is " << dd_psc_2_o(0.0) << '\n';

    nth_derivative<2, psc_f, double> dd_psc_3_o(psc_f(1.0), 0.001);
    cout << "2nd derivative of sin(0) + cos(0) is " << dd_psc_3_o(0.0) << '\n';

    nth_derivative<6, psc_f, double> d6_psc_o(psc_f(1.0), 0.00001);
    cout << "6th derivative of sin(0) + cos(0) is " << d6_psc_o(0.0) << '\n';

    nth_derivative<12, psc_f, double> d12_psc_o(psc_f(1.0), 0.00001);
    cout << "12th derivative of sin(0) + cos(0) is " << d12_psc_o(0.0) << '\n';

    // nth_derivative<7>{psc_o, 0.0001}; // compile error
    // nth_derivative<7, decltype(psc_o), decltype(0.00001)>{psc_o, 0.0001}; // dirty
    // use template function to deduce the template parameter types of functor

    derive<7, psc_f, double>(psc_o, 0.00001);
    auto d7_psc_o= derive<7>(psc_o, 0.00001);

    cout << "7th derivative of psc_o at x=3 is "
         << derive<7>(psc_o, 0.00001)(3.0) << '\n';


    return 0;
}
