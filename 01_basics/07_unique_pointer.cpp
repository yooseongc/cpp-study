#include <iostream>
#include <memory>

using namespace std;

unique_ptr<double> f()
{
    return unique_ptr<double>{new double};
}

int main()
{
    unique_ptr<double> dp{new double};
    *dp = 7;
    cout << "The value of *dp is " << *dp << endl;

    // double d = 7.2;
    // unique_ptr<double> dd{&d};  // bug code

    // unique_ptr<double> dp2{dp}; // bug code
    // unique_ptr<double> dp2{}; dp2 = dp; // bug code

    unique_ptr<double> dp2{move(dp)}, dp3{};
    dp3 = move(dp2);

    unique_ptr<double> dp4;
    dp4 = f();  // RVO: intrinsic move semantics for temporary object

    // unique_ptr specialized to native array
    unique_ptr<double[]> da{new double[3]};
    for(unsigned i = 0; i < 3; ++i)
    {
        da[i] = i + 2;
    }

    return 0;
}
