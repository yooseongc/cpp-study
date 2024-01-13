#include <iostream>
#include <cmath>
#include <functional>
#include <vector>
#include <complex>
#include <typeinfo>

using namespace std;

double add(double x, double y)
{
    return x + y;
}

inline double sub(double x, double y)
{
    return x - y;
}

struct mult
{
    double operator()(double x, double y) const
    {
        return x * y;
    }
};

template <typename Value>
struct power
{
    Value operator()(Value x, Value y) const
    {
        return pow(x, y);
    }
};

struct greater_t
{
    template <typename Value>
    Value operator()(Value x, Value y) const
    {
        return x > y;
    }
} greater_than;

struct dummy
{
    operator double()
    {
        return 4.0;
    }
};

struct helper
{
    double maxm(double x, double y) const
    {
        return x >= y ? x : y;  // not for std::function
    }

    static double max(double x, double y)
    {
        return x >= y ? x : y;
    }
};

int main()
{
    using bin_fun = function<double(double, double)>;

    bin_fun f = &add;
    cout << "f(6, 3) = " << f(6, 3) << endl;

    helper h;
    f = [h](double x, double y){ return h.max(x, y); };
    f = [](double x, double y){ helper h; return h.max(x, y); };
    f = bind(&helper::maxm, h, placeholders::_1, placeholders::_2);

    vector<bin_fun> functions;
    functions.push_back(&add);
    // functions.push_back(add);
    // functions.push_back(&sub);
    functions.push_back(sub);
    functions.push_back(mult{});
    functions.push_back(power<double>{});
    functions.push_back(greater_than);
    functions.push_back([](double x, double y){ return x / y; });
    // functions.push_back([](double x, double y){ return complex<double>(3); });

    functions.push_back(helper::max);
    // functions.push_back(helper::maxm);
    functions.push_back(bind(&helper::maxm, h, placeholders::_1, placeholders::_2));
    functions.push_back([](double x, double y){ helper h; return h.max(x, y); });

    for (auto& f : functions)
    {
        cout << "f(6, 3) = " << f(6, 3) << endl;
    }

    dummy d;
    cout << "functions[5](d, d) = " << functions[5](d, d) << endl;

    return 0;
}
