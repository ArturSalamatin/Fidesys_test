#ifndef SOLVER_H
#define SOLVER_H

#include <unordered_map>
#include <omp.h>
#include "../eigen/Eigen/SparseCore"
#include "../eigen/Eigen/SparseLU"

//#include "../ModelGenerator/ModelDescriptor.h"
#include "../LagrangeElements/LagrangeElements.h"

namespace Solver
{
    using SparseMatrix = Eigen::SparseMatrix<double, Eigen::RowMajor>;
    using Vector = Eigen::VectorXd;
    using MatrixSolver = Eigen::SparseLU<SparseMatrix>;

    /**
     * @brief Class that describes Ax=b problem
     *
     */
    template <unsigned char dof>
    class ProblemDesc
    {
    public:
        ProblemDesc(const ModelDescriptor::GridDesc &gridDesc,
                    const ModelDescriptor::MaterialPropDesc &propDesc) noexcept
        {
            auto pCount{gridDesc.PointsCount()};
            auto eCount{gridDesc.ElementsCount()};

            problem_size = pCount * dof;

            ModelDescriptor::PlainStressMaterialMatrix c{propDesc};
            lagrElems.resize(gridDesc.ElementsCount());

// #pragma omp parallel for
            for (size_t l = 0; l < gridDesc.ElementsCount(); ++l)
            //  for (const auto &[key, value] : gridDesc.elements)
            {
                lagrElems.emplace(l, value,
                                  propDesc,
                                  c);
            }
        }

        const SparseMatrix &Matrix() const noexcept
        {
            return A;
        }
        const Vector &RHS() const noexcept
        {
            return b;
        }

        unsigned int size() { return problem_size; }

    protected:
        ModelDescriptor::GridDesc gridDesc;
        std::vector<TLLE::LagrangeElement> lagrElems;
        SparseMatrix A;
        Vector b;
        unsigned int problem_size;

        void set_A(const std::vector<TLLE::LagrangeElement> &lagrElems) noexcept
        {
            A = SparseMatrix{problem_size, problem_size};
            for (size_t l = 0; l < lagrElems.size(); ++l)
            {
                const auto &K = lagrElems[l].K;
                const auto &globalNodeId = gridDesc.elementsDesc[l];
            }
        }
        void set_b() noexcept
        {
            b = Vector(problem_size);
            for (auto &it : b)
                it = 0.0;
        }
    };

    /**
     * @brief Solver is responsible for solving a problem Ax=b
     * with specified matrix A and rhs b
     *
     */
    template <unsigned char dof>
    class Solver
    {
    protected:
        Vector x;
        MatrixSolver solver;

    public:
        Solver(const ModelDescriptor::GridDesc &gridDesc) noexcept;

        bool solve(const ProblemDesc<dof> &desc)
        {
            solver.compute(desc.Matrix());
            if (solver.info() != Eigen::Success)
            {
                // decomposition failed
                return false;
            }
            solver.solve(desc.RHS());
            if (solver.info() != Eigen::Success)
            {
                // solving failed
                return false;
            }
        }
        const Vector &Solution() const { return x; }
    };

} // Solver

#endif