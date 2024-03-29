#include <cassert>
#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std::chrono;

template <typename T>
class vector
{
    void check_size(int that_size) const { assert(my_size == that_size); }
    void check_index(int i) const { assert(i >= 0 && i < my_size); }

    public:
        explicit vector(int size) : my_size(size), data(new T[my_size]) {}
        vector() : my_size(0), data(0) {}
        vector(const vector& that) : my_size(that.my_size), data(new T[my_size])
        {
            std::copy(&that.data[0], &that.data[0] + my_size, data[0]);
        }

        ~vector() { if(data) delete[] data; }

        vector& operator=(const vector& that)
        {
            check_size(that.my_size);
            std::copy(&that.data[0], &that.data[0] + my_size, data[0]);
        }

        int size() const { return my_size; }

        const T& operator[](int i) const
        {
            check_index(i);
            return data[i];
        }

        T& operator[](int i)
        {
            check_index(i);
            return data[i];
        }
    
    private:
        int my_size;
        T* data;
};

template <typename Value>
std::ostream& operator<<(std::ostream& os, const vector<Value>& v)
{
    os << '[';
    if (v.size() > 0)
        os << v[0];
    for (int i = 1; i < v.size(); ++i)
        os << ", " << v[i];
    return os << ']';
}

template <unsigned Offset, unsigned Max>
struct my_axpy_ftor
{
    template <typename U, typename V, typename W>
    static void eval(U& u, const V& v, const W& w, unsigned i)
    {
        if constexpr(Offset < Max)
        {
            u[i + Offset] = 3.0f * v[i + Offset] + w[i + Offset];
            my_axpy_ftor<Offset+1, Max>::eval(u, v, w, i);
        }
    }
};

template <unsigned BSize, typename U, typename V, typename W>
void my_axpy(U& u, const V& v, const W& w)
{
    assert(u.size() == v.size() && v.size() == w.size());
    unsigned s = u.size(), sb = s / BSize * BSize;

    for(unsigned i = 0; i < sb; i += BSize)
    {
        my_axpy_ftor<0, BSize>::eval(u, v, w, i);
    }

    for(unsigned i = sb; i < s; i++)
    {
        u[i] = 3.0f * v[i] + w[i];
    }
}

template <typename TP>
double duration_ms(const TP& from, const TP& to, unsigned rep)
{
    return duration_cast<nanoseconds>(to - from).count() / 1000. / rep;
}

template <typename TP>
double duration_ns(const TP &from, const TP &to, unsigned rep)
{
    return duration_cast<nanoseconds>(to - from).count() / rep;
}

int main()
{
    unsigned s = 1000;
    vector<float> u(s), v(s), w(s);

    for(unsigned i = 0; i < s; i++)
    {
        v[i] = float(i);
        w[i] = float(2 * i + 15);
    }

    for(unsigned j = 0; j < 3; j++)
    {
        for(unsigned i = 0; i < s; i++)
        {
            u[i] = 3.0f + v[i] + w[i];
        }
    }

    constexpr unsigned rep = 1000000;

    using TP = time_point<steady_clock>;

    TP nat = steady_clock::now();
    for(unsigned j = 0; j < rep; j++)
    {
        for(unsigned i = 0; i < s; i++)
        {
            u[i] = 3.0f * v[i] + w[i];
        }
    }
    TP nat_end = steady_clock::now();
    std::cout << "Compute time native loop is " << duration_ns(nat, nat_end, rep) << " ns.\n";
    std::cout << "u[0] is " << u[0] << '\n';

    TP unr = steady_clock::now();
    for(unsigned j = 0; j < rep; j++)
    {
        unsigned sb = s / 4 * 4;
        for(unsigned i = 0; i < sb; i += 4)
        {
            u[i] = 3.0f * v[i] + w[i];
            u[i+1] = 3.0f * v[i+1] + w[i+1];
            u[i+2] = 3.0f * v[i+2] + w[i+2];
            u[i+3] = 3.0f * v[i+3] + w[i+3];
        }
        for(unsigned i = sb; i < s; i++)
        {
            u[i] = 3.0f * v[i] + w[i];
        }
    }
    TP unr_end = steady_clock::now();
    std::cout << "Compute time unrolled loop is " << duration_ns(unr, unr_end, rep) << " ns.\n";
    std::cout << "u[0] is " << u[0] << '\n';

    TP unr2 = steady_clock::now();
    for(unsigned j = 0; j < rep; j++)
    {
        my_axpy<2>(u, v, w);
    }
    TP unr2_end = steady_clock::now();
    std::cout << "Compute time unrolled loop is " << duration_ms(unr2, unr2_end, rep) << " mmicros.\n";
    std::cout << "u[0] is " << u[0] << '\n';

    TP unr4 = steady_clock::now();
    for (unsigned j = 0; j < rep; j++)
        my_axpy<4>(u, v, w);
    TP unr4_end = steady_clock::now();
    std::cout << "Compute time unrolled loop is " << duration_ms(unr4, unr4_end, rep) << " mmicros.\n";
    std::cout << "u[0] is " << u[0] << '\n';

    TP unr6 = steady_clock::now();
    for (unsigned j = 0; j < rep; j++)
        my_axpy<6>(u, v, w);
    TP unr6_end = steady_clock::now();
    std::cout << "Compute time unrolled loop is " << duration_ms(unr6, unr6_end, rep) << " mmicros.\n";
    std::cout << "u[0] is " << u[0] << '\n';

    TP unr8 = steady_clock::now();
    for (unsigned j = 0; j < rep; j++)
        my_axpy<8>(u, v, w);
    TP unr8_end = steady_clock::now();
    std::cout << "Compute time unrolled loop is " << duration_ms(unr8, unr8_end, rep) << " mmicros.\n";
    std::cout << "u[0] is " << u[0] << '\n';

    return 0;
}
