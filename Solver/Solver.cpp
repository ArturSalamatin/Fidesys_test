#include "Solver.h"

bool Solver::Solver::solve()
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