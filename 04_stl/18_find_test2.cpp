#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;


int main(int argc, char** argv)
{
    std::list<int> seq = { 3, 4, 7, 9, 2, 5, 7, 8 };

    auto it  = find(begin(seq), end(seq), 7);
    auto it2 = it;
    ++it2;

    auto past = find(it2, end(seq), 7);
    ++past;

    for(; it != past; ++it)
    {
        std::cout << *it << ' ';
    } 
    std::cout << '\n';

    return 0;
}
