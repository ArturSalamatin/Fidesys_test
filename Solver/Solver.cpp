#include "Solver.h"

namespace Solver
{

    bool Solver::solve()
    {
        solver.compute(A);
        if (solver.info() != Eigen::Success)
        {
            // decomposition failed
            return;
        }
        x = solver.solve(b);
        if (solver.info() != Eigen::Success)
        {
            // solving failed
            return;
        }
    }

    ProblemDesc::ProblemDesc(const ModelDescriptor::GridDesc &gridDesc) noexcept
        : gridDesc{gridDesc}
    {
    }

    const SparseMatrix& ProblemDesc::Matrix() const noexcept
    {
        return A;
    }
    const Vector& ProblemDesc::RHS() const noexcept
    {
        return b;
    }
    const Vector& ProblemDesc::Solution() const noexcept
    {
        return x;
    }
} // Solver