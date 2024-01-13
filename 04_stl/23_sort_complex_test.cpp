#include <iostream>
#include <vector>
#include <complex>
#include <iterator>
#include <algorithm>

using namespace std;

int main()
{
    std::vector<int> seq = {3, 4, 7, 9, 2, 5, 7, 8, 3, 4, 3, 9};
    sort(begin(seq), end(seq), [](const int& x, const int& y){ return x > y; });
    copy(begin(seq), end(seq), ostream_iterator<int>(cout, ", "));
    cout << endl;

    using cf = complex<float>;
    std:vector<cf> v = {{3, 4}, {7, 9}, {2, 5}, {7, 8}};
    sort(begin(v), end(v), [](const cf& x, const cf& y){ return abs(x) < abs(y); });
    copy(begin(v), end(v), ostream_iterator<cf>(cout, ", "));
    cout << endl;

    // parentheses around && expression requested by pedantic compilers
    auto lex = [](const cf& x, const cf& y){ return real(x) < real(y) || (real(x) == real(y) && imag(x) < imag(y)); };
    sort(begin(v), end(v), lex);
    copy(begin(v), end(v), ostream_iterator<cf>(cout, ", "));
    cout << endl;

    return 0;
}
