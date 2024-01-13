#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

atomic<int> cnt(0);
void f() { for(int i = 0; i < 1000000; ++i, ++cnt); }

int main()
{
    auto t1 = high_resolution_clock::now();
    
    vector<thread> v;   
    
    for(int i = 0; i < 10; ++i)
    {
        v.emplace_back(thread(f));
    }

    for(auto& t : v)
    {
        t.join();
    }
    
    auto t2 = high_resolution_clock::now();
    cout << "cnt = " << cnt << ", time = " << duration_cast<microseconds>(t2 - t1).count() << "ms." << endl;
    return 0;
}
