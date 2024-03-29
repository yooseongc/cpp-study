#ifndef OUR_COMPLEX_INCLUDE
#define OUR_COMPLEX_INCLUDE

#include <iostream>
#include <cmath>

class complex
{
    public:
        complex(double r, double i) : r{r}, i{i} {}
        complex(double r) : r{r} {}
        complex() {}

        complex& operator=(const complex& c)
        {
            r = c.r;
            i = c.i;
            return *this;
        }

        complex& operator=(double rn)
        {
            r = rn;
            i = 0.0;
            return *this;
        }

        complex operator+(double d) const;

        friend inline double const& real(const complex& c)
        {
            return c.r;
        }

        friend inline double& real(complex& c)
        {
            return c.r;
        }

        friend inline double const& imag(const complex& c)
        {
            return c.i;
        }

        friend inline double& imag(complex& c)
        {
            return c.i;
        }

        friend complex operator-(const complex& c1, const complex& c2)
        {
            return {c1.r - c2.r, c1.i - c2.i};
        }

    private:
        double r = 0.0;
        double i = 0.0;
};

inline complex operator+(const complex& c1, const complex& c2)
{
    return complex(real(c1) + real(c2), imag(c1) + imag(c2));
}

inline complex operator+(double d, const complex& c2)
{
    return complex(d + real(c2), imag(c2));
}

inline complex complex::operator+(double d) const
{
    return complex(r + d, i);
}

inline complex operator*(const complex& c1, const complex& c2)
{
    return complex(
        real(c1) * real(c2) - imag(c1) * imag(c2),
        real(c1) * imag(c2) + imag(c1) * real(c2)
    );
}

inline double abs(const complex& c)
{
    return std::sqrt(real(c) * real(c) + imag(c) * imag(c));
}

complex operator-(const complex& c1)
{
    std::cout << "free unary -\n";
    return complex(-real(c1), -imag(c1));
}

std::ostream& operator<<(std::ostream& os, complex c)
{
    os << '(' << real(c) << ',' << imag(c) << ')';
    return os;
}

#endif
