#include <iostream>
#include <memory>

using namespace std;

shared_ptr<double> f()
{
    shared_ptr<double> p1{new double};
    shared_ptr<double> p2{new double}, p3 = p1; // copy p1 to p3
    cout << "p3.use_count() = " << p3.use_count() << endl;
    return p3;
}

int main()
{
    shared_ptr<double> p = f();
    cout << "p.use_count() = " << p.use_count() << endl;

    // recommend to use make_shared
    auto p1 = make_shared<double>();

    return 0;
}
