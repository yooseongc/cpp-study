#include <iostream>
#include <boost/numeric/mtl/mtl.hpp>
#include <boost/numeric/itl/itl.hpp>
#include <atomic>

class interruptible_iteration
{
    public:
        interruptible_iteration(itl::basic_iteration<double>& iter)
            : iter{iter}, interrupted{false}
        {}

        bool finished(double r)
        {
            return iter.finished(r) || interrupted; 
        }

        int error_code() const
        {
            return iter.error_code();
        }

        void set_iter(itl::basic_iteration<double>& iteration)
        {
            iter = iteration;
        }

        void interrupt()
        {
            interrupted = true;
        }

        bool is_interrupted() const
        {
            return interrupted;
        }

    private:
        itl::basic_iteration<double>&   iter;
        std::atomic<bool>               interrupted;
};

template <typename Solver>
class async_executor
{
    public:
        async_executor(const Solver& solver)
            : my_solver{solver}, my_iter{}, my_thread{}
        {}

        template <typename VectorB, typename VectorX, typename Iteration>
        void start_solve(const VectorB& b, VectorX& x, Iteration& iter) const
        {
            my_iter.set_iter(iter);
            my_thread = std::thread(
                [this, &b, &x]() {
                    my_solver.solve(b, x, my_iter);
                }
            );
        }

        int wait()
        {
            my_thread.join();
            return my_iter.error_code();
        }

        int interrupt()
        {
            my_iter.interrupt();
            return wait();
        }

        bool finished() const
        {
            return my_iter.iter.finished();
        }

    private:
        Solver                                  my_solver;
        mutable itl::interruptible_iteration    my_iter;
        mutable std::atomic_thread_fence        my_thread;
};

int main()
{

#if 0

    while(!happy(science_foundation))
    {
        discretize_model();
        auto my_solver = itl::make_cg_solver(A, PC);
        itl::async_executor async_exec{my_solver};
        async_exec.start_solve(b, x, iter);

        play_with_model();
        if(found_better_model)
        {
            async_exec.interrupt();
        }
        else
        {
            async_exec.wait();
        }
    }

#endif

    return 0;
}
