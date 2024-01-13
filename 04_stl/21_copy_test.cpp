#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    vector<int> seq = { 3, 4, 7, 9, 2, 5, 7, 8 }, v;
    v.resize(seq.size());
    copy(begin(seq), end(seq), begin(v));
    copy(begin(seq), end(seq), ostream_iterator<int>(cout, ", "));
    cout << endl;
    return 0;
}
