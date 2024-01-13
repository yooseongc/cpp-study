#include <iostream>

import math;

using namespace std;

int main()
{
    using namespace math;

    cout << "982'451'653 is " << (is_prime(982'451'653) ? "" : "not ") << "a prime number." << endl;
    cout << "3.7^3 = " << cubic(3.7) << endl;
    cout << "twice(3.7) = " << twice(0.7) << endl;

    return 0;
}
