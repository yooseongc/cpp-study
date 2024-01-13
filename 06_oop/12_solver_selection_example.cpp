#include <iostream>
#include <memory>
#include <cstdlib>

class matrix {};
class vector {};

void cg(const matrix& A, const vector& b, vector& x)
{
    std::cout << "CG" << std::endl;
}

void bicg(const matrix& A, const vector& b, vector& x)
{
    std::cout << "BiCG" << std::endl;
}

struct solver
{
    virtual void operator()(const matrix& A, const vector& b, vector& x) = 0;
    virtual ~solver() {}
};

// potentially templatize
struct cg_solver : solver
{
    virtual void operator()(const matrix& A, const vector& b, vector& x) override
    {
        cg(A, b, x);
    }
};

struct bicg_solver : solver
{
    virtual void operator()(const matrix& A, const vector& b, vector& x) override
    {
        bicg(A, b, x);
    }
};

int main(int argc, char** argv)
{
    using namespace std;
    matrix A;
    vector b, x;

    int solver_choice = argc >= 2 ? std::atoi(argv[1]) : 0;
    switch(solver_choice)
    {
        case 0: cg(A, b, x); break;
        case 1: bicg(A, b, x); break;
    }

    // Factory
    unique_ptr<solver> my_solver;
    switch(solver_choice)
    {
        case 0: my_solver = unique_ptr<cg_solver>{new cg_solver}; break;
        //                  make_unique<cg_solver>(); break;
        case 1: my_solver = unique_ptr<bicg_solver>{new bicg_solver}; break;
        //                  make_unique<bicg_solver>(); break;
    }

    (*my_solver)(A, b, x);

    return 0;
}
