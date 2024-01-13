#include <iostream>

using namespace std;

class complex
{
    public:
        double r, i;

        // complex(double rnew, double inew)
        // {
        //     r = rnew; i = inew;
        // }

        complex(double r, double i) : r(r), i{i} {}
        complex(double r) : r{r}, i{0} {}
        complex() : r{0}, i{0} {}                      // default constructor
        complex(const complex& c) : r{c.r}, i{c.i} {}  // copy constructor
        // complex(const complex& c) = default;
        // complex(complex c) {}  // --> ERROR
};

int main()
{
    // complex z, c;
    // z.r = 3.5; z.i = 2;
    // c.r = 2; c.i = -3.5;
    complex z(3.5, 2);
    complex c{2, -3.5};

    cout << "z is (" << z.r << ", " << z.i << ")\n";

    complex z1,         // default constructor
            z2(),       // most vexing parse : function definition
            z3{4},      // z3{4, 0}
            z4 = 4,     // z4{4, 0}
            z5{0, 1};   

    complex z6(z);  // copy
    complex z7{z};  // copy

    return 0;
}
