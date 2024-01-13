#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>

using namespace std;
using namespace std::chrono;

inline double my_root(double x, double eps=1e-12)
{
    double sq = 1.0, sqo;
    do
    {
        sqo = sq;
        sq = 0.5 * (sqo + x / sqo);
    } 
    while(abs(sq - sqo) > eps);

    return sq;
}

int main()
{
    time_point<system_clock> now = system_clock::now();
    time_point<system_clock> then = now + hours(2);
    time_t then_time = system_clock::to_time_t(then);
    cout << "Daring, I'll be with you at " << ctime(&then_time);

    const int rep = 100000;
    double r3;

    time_point<steady_clock> start = steady_clock::now();
    for(int i = 0; i < rep; i++)
    {
        r3 = my_root(3.0);
    }
    auto end = steady_clock::now();

    cout << "my_root(3.0) = " << r3 << ", the calculation took " << (end - start).count() / rep << " ticks" << endl;
    cout << "my_root(3.0) = " << r3 << ", the calculation took " << duration_cast<microseconds>(end - start).count() / rep << " ms" << endl;
    cout << "my_root(3.0) = " << r3 << ", the calculation took " << duration_cast<nanoseconds>(end - start).count() / 1000. / rep << " ms" << endl;

    using P = steady_clock::period; // type of time unit
    cout << "Resolution is " << double { P::num } / P::den << "s." << endl;

    return 0;
}
