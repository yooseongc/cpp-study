#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <string>

namespace dmc
{
    struct trivial_nonprime {};

    bool is_prime(long i)
    {
        if(i % 10 == 5 && i != 5)
        {
            throw trivial_nonprime{};
        }

        if(i == 1)
        {
            return false;
        }

        if(i % 2 == 0)
        {
            return i == 2;
        }

        for(long j = 3; j < i; j += 2)
        {
            if(i % j == 0)
            {
                return false;
            }
        }

        return true;
    }
}

int main(int argc, char* argv[])
{
    using namespace std;
    using namespace dmc;
    
    int num_threads = 2;
    if(argc > 1)
    {
        num_threads = stoi(argv[1]);
    }

    vector<long> vi;
    for(long v = 982451653, i = 0; i < num_threads; ++i, v += 2)
    {
        vi.emplace_back(v);
    }

    vector<future<bool> > vf;
    for(long v : vi)
    {
        vf.emplace_back(async(is_prime, v));
    }

    for(long i = 0; i < num_threads; ++i)
    {
        try
        {
            while(vf[i].wait_for(200ms) != future_status::ready)
            {
                cout << "Still waiting " << i <<"th thread." << endl;
            }
            cout << vi[i] << (vf[i].get() ? " is " : " is not ") << "a prime number." << endl;
        }
        catch (trivial_nonprime)
        {
            cout << " is obviously not a prime number, moron." << endl;
        }
    }

    return 0;
}
