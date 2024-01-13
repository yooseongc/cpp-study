#include <iostream>

using namespace std;


double& square_ref(double d) // bug : stale reference
{
    double s = d * d;
    return s;  // bug
}

double* square_ptr(double d) // bug : dangling pointer
{
    double s = d * d;
    return &s; // bug
}

int main()
{
    int i = 5;
    int& j = i;
    j = 4;
    cout << "i = " << i << '\n';

    return 0;
}
