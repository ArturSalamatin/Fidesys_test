
#include "../eigen/Eigen/Core"
#include "../Solver/Solver.h"

namespace TestSpace
{
 //   double tol;

    Eigen::Vector2d getDisplacement(size_t id, const Solver::Vector &sol);

    bool comp(double val, double control = 0.0);

} // TestSpace