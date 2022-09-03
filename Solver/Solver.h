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

    public:
        Solver(const ModelDescriptor::GridDesc &gridDesc) noexcept;

        bool solve();
    };

    using SparseMatrix = Eigen::SparseMatrix<double, Eigen::RowMajor>;
    using Vector = Eigen::VectorXd;
    using MatrixSolver = Eigen::SparseLU<SparseMatrix>;

    /**
     * @brief Class that describes Ax=b problem
     *
     */
    class ProblemDesc
    {
        public:
        ProblemDesc(const ModelDescriptor::GridDesc& gridDesc) noexcept;

        void set_A() noexcept;
        void set_b() noexcept;

        const SparseMatrix& Matrix() const noexcept;
        const Vector& RHS() const noexcept;
        const Vector& Solution() const noexcept;

    protected:
        ModelDescriptor::GridDesc gridDesc;

    protected:
        SparseMatrix A; //(1000,1000);
        Vector b;
        Vector x;

        MatrixSolver solver;
    };

} // Solver

#endif