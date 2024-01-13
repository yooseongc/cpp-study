#include <iostream>
#include <vector>
#include <valarray>
#include <cassert>


void vector_add(const std::vector<float>& v1, const std::vector<float>& v2, std::vector<float>& s)
{
    assert(v1.size() == v2.size());
    assert(v1.size() == s.size());
    for (unsigned i = 0; i < v1.size(); ++i)
    {
        s[i] = v1[i] + v2[i];
    }
}

std::vector<float> add(const std::vector<float>& v1, const std::vector<float>& v2)
{
    assert(v1.size() == v2.size());
    std::vector<float> s(v1.size());
    for (unsigned i = 0; i < v1.size(); ++i)
    {
        s[i] = v1[i] + v2[i];
    }
    return s;
}

int main()
{
    std::vector<float> v(3), w(3), s(3);
    v[0] = 1; v[1] = 2; v[2] = 3;
    w[0] = 7, w[1] = 8; w[2] = 9;
    vector_add(v, w, s);

    std::vector<float> vv = {1, 2, 3}, ww = {7, 8, 9}, ss = add(vv, ww);

    std::valarray<float> vvv = {1, 2, 3}, www = {7, 8, 9}, sss = vvv + 2.0f * www;
    vvv = std::sin(sss);
    for (float x : vvv)
    {
        std::cout << x << ' ';
    }
    std::cout << '\n';


    return 0;
}
