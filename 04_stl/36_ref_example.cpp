#include <iostream>
#include <vector>
#include <functional>
#include <iterator>
#include <map>

using namespace std;

int main()
{
    // std::vector<int&> v;
    vector<int> v1 = { 2, 3, 4 }, v2 = { 5, 6 }, v3 = { 7, 8 };
    vector<int> v4;
    v4.push_back(3);
    int i = 7;
    v4.push_back(i);

    // vector<vector<int>&> vv;
    vector<reference_wrapper<vector<int> > > vv;
    vv.push_back(v1);
    vv.push_back(v2);
    vv.push_back(v3);
    vv.push_back(v2);
    vv.push_back(v1);
    vv[0] = v3;

    for(const vector<int>& vr : vv)
    {
        copy(begin(vr), end(vr), ostream_iterator<int>(cout, ", "));
        cout << endl;
    }

    // vector<decltype(ref(v1))> vv;
    // map<int, decltype(ref(v1))> mv;
    map<int, reference_wrapper<vector<int> > > mv;
    mv.emplace(4, v1);
    mv.emplace(7, v2);
    mv.insert(make_pair(8, ref(v3)));
    mv.insert(make_pair(9, ref(v2)));

    for(const auto& vr : mv)
    {
        cout << vr.first << ": ";
        for(int i : vr.second.get())
        {
            cout << i << ", ";
        }
        cout << endl;
    }

    auto& e7 = mv.find(7)->second;
    copy(begin(e7.get()), end(e7.get()), ostream_iterator<int>(cout, ", "));
    cout << endl;

    return 0;
}
