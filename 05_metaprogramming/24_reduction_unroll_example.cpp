#include <cmath>
#include <cassert>
#include <iostream>
#include <chrono>

using namespace std::chrono;

template <typename T>
class vector
{
    void check_size(int that_size) const { assert(my_size == that_size); }
    void check_index(int i) const { assert(i >= 0 && i < my_size); }

public:
    typedef T value_type;

    explicit vector(int size) : my_size(size), data(new T[my_size]) {}
    vector() : my_size(0), data(0) {}

    vector(const vector& that)
        : my_size(that.my_size), data(new T[my_size])
    {
        for(int i = 0; i < my_size; ++i)
        {
            data[i] = that.data[i];
        }
    }
    
    ~vector() { if(data) delete[] data; }

    vector& operator=(const vector& that)
    {
        check_size(that.my_size);
        for(int i = 0; i < my_size; ++i)
        {
            data[i] = that.data[i];
        }
        return *this;
    }

    template <typename Src>
    vector& operator=(const Src& that)
    {
        check_size(size(that));
        for(unsigned i = 0; i < my_size; i++)
        {
            data[i] = that[i];
        }
        return *this;
    }

    friend int size(const vector& x) { return x.my_size; }

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
struct one_norm_ftor
{
    template <typename S, typename V>
    static void eval(S& sum, const V& v, unsigned i)
    {
        using std::abs;
        if constexpr(Offset < Max)
        {
            sum += abs(v[i + Offset]);
            // std::cout << "sum[" << Offset << "]+= abs(v[" << i << "+" << Offset << "])\n";
            one_norm_ftor<Offset+1, Max>::eval(sum, v, i);
        }
    }
};

template <unsigned BSize, typename Vector>
typename Vector::value_type
inline one_norm(const Vector& v)
{
    using std::abs;
    typename Vector::value_type sum(0);
    unsigned s = size(v), sb = s / BSize * BSize;

    for(unsigned i = 0; i < sb; i += BSize)
    {
        one_norm_ftor<0, BSize>::eval(sum, v, i);
    }

    for(unsigned i = sb; i < s; i++)
    {
        sum += abs(v[i]);
    }

    return sum;
}

template <typename TP>
double duration_ms(const TP& from, const TP& to, unsigned rep)
{
    return duration_cast<nanoseconds>((to - from) / rep).count() / 1000.;

}

template <unsigned BSize, typename Vector>
void inline bench_unroll(const Vector& v, const unsigned rep)
{
    typename Vector::value_type norm;
    auto t1 = steady_clock::now();
    for(unsigned j = 0; j < rep; j++)
    {
        norm = one_norm<BSize>(v);
    }
    auto t2 = steady_clock::now();
    std::cout << "Compute time one_norm<" << BSize << ">(v) is " << duration_ms(t1, t2, rep) << " ms." << std::endl;
}

int main()
{
    unsigned s = 1000;
    vector<float> u(s), v(s), w(s);
    for(unsigned i = 0; i < s; i++)
    {
        v[i] = float(i);
        w[i] = float(2*i + 15);
    }

    const unsigned rep = 200000;

    bench_unroll<1>(v, rep);
    bench_unroll<2>(v, rep);
    bench_unroll<4>(v, rep);
    bench_unroll<6>(v, rep);
    bench_unroll<8>(v, rep);

    return 0;
}
