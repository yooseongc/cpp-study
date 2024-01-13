#ifndef ODE_SOLVER_RESIZE_HPP
#define ODE_SOLVER_RESIZE_HPP

#include <vector>
#include <array>

namespace ode_solver
{
    template <typename state_type>
    void resize(const state_type& in, state_type& out)
    {
        out.resize(in.size());
    }

    template <typename T, std::size_t N>
    void resize(const std::array<T, N>&, std::array<T, N>&)
    {
        // arrays don't need resizing
    }
}

#endif
