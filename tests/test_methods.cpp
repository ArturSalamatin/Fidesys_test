
#include "test_methods.h"

namespace TestSpace
{
    double tol = 1E-14;

    Eigen::Vector2d getDisplacement(size_t id, const Solver::Vector &sol)
    {
        return Eigen::Vector2d{sol(2 * id), sol(2 * id + 1)};
    }

    bool comp(double val, double control)
    {
        return std::abs(val - control) < tol;
    }

} // TestSpace