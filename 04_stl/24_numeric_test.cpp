#include <iostream>
#include <vector>
#include <complex>
#include <iterator>
#include <algorithm>
#include <numeric>

using namespace std;

template <typename T>
    requires requires { typename T::value_type; }
void print(const T &v)
{
    copy(begin(v), end(v), ostream_iterator<typename T::value_type>(cout, ", "));
    cout << endl;
}

int main()
{
    vector<float> v = {3.1f, 4.2f, 7, 9.3f, 2, 5, 7, 8, 3, 4},
                  w(10), x(10), y(10);
    
    iota(begin(w), end(w), 12.1);
    partial_sum(begin(v), end(v), begin(x));
    adjacent_difference(begin(v), end(v), begin(y));
    float alpha = inner_product(begin(w), end(w), begin(v), 0.0f);
    float sum_w = accumulate(begin(w), end(w), 0.0f);
    float product_w = accumulate(begin(w), end(w), 1.0f, [](const float& x, const float& y) { return x * y; });

    print(w);
    print(x);
    print(y);

    cout << "alpha = " << alpha << endl;
    cout << "sum_w = " << sum_w << endl;
    cout << "product_w = " << product_w << endl;

    return 0;
}
