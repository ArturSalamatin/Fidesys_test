#ifndef SOLVER_H
#define SOLVER_H

#include "../ModelGenerator/ModelDescriptor.h"
#include "../eigen/Eigen/SparseCore"
#include "../eigen/Eigen/SparseLU"

namespace Solver
{
    /**
     * @brief Solver is responsible for solving a problem Ax=b
     * with specified matrix A and rhs b
     *
     */
    class Solver
    {
        using Matrix = Eigen::SparseMatrix<double, Eigen::RowMajor>;
        using Vector = Eigen::VectorXd;
        using MatrixSolver = Eigen::SparseLU<Matrix>;

    protected:
        ModelDescriptor::GridDesc gridDesc;

    protected:
        Matrix A; //(1000,1000);
        Vector b;
        Vector x;

        MatrixSolver solver;

    public:
        Solver(const ModelDescriptor::GridDesc &gridDesc) noexcept;

        bool solve();
    };
} // Solver

#endif