#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <unordered_map>
// #include <omp.h>
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
    template <unsigned char lnc, unsigned char dof>
    class ProblemDesc
    {
    public:
        ProblemDesc(const ModelDescriptor::GridDesc &gridDesc,
                    const ModelDescriptor::MaterialPropDesc &propDesc) noexcept
            : gridDesc{gridDesc}
        {
            auto pCount{gridDesc.PointsCount()};
            auto eCount{gridDesc.ElementsCount()};

            problem_size = pCount * dof;

            ModelDescriptor::PlainStressMaterialMatrix c{propDesc};
            lagrElems.reserve(gridDesc.ElementsCount());

            // #pragma omp parallel for
            for (size_t l = 0; l < gridDesc.ElementsCount(); ++l)
            //  for (const auto &[key, value] : gridDesc.elements)
            {
                lagrElems.emplace_back(gridDesc.elements[l],
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

        size_t size() { return problem_size; }

    public:
        ModelDescriptor::GridDesc gridDesc;
        std::vector<TLLE::LagrangeElement> lagrElems;
        SparseMatrix A;
        Vector b;
        size_t problem_size;

        void set_A() noexcept
        {
            using T = Eigen::Triplet<double>;
            size_t nnz = static_cast<size_t>(std::pow(dof * lnc * gridDesc.ElementsCount(), 2.0)); // total number of elements in all stiffness submatricies
            std::vector<T> coefficients;
            coefficients.reserve(nnz);

            for (size_t L = 0; L < lagrElems.size(); ++L)
            {
                const auto &K = lagrElems[L].K;
                const auto &globalNodeId = gridDesc.elementsDesc[L];
                // (i;j) -- loop through the local stiffness submatriceis
                for (size_t i = 0; i < lnc; ++i)
                {
                    for (size_t j = 0; j < lnc; ++j)
                    {
                        const auto &sm = K[i][j];
                        // (k;l) -- loop through scalar values of a (i;j) stiffness submatrix
                        for (size_t k = 0; k < dof; ++k)
                        {
                            for (size_t l = 0; l < dof; ++l)
                            {
                                if (sm(k, l) != 0.0)
                                {
                                    // global stiffness matrix coordinates
                                    size_t I = globalNodeId(i) * dof + k;
                                    size_t J = globalNodeId(j) * dof + l;

                                    coefficients.emplace_back(I, J, sm(k, l));
                                }
                            }
                        }
                    }
                }
            }

            A = SparseMatrix(problem_size, problem_size);
            A.setFromTriplets(coefficients.begin(), coefficients.end());
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

        // bool solve(const ProblemDesc<dof> &desc)
        // {
        //     solver.compute(desc.Matrix());
        //     if (solver.info() != Eigen::Success)
        //     {
        //         // decomposition failed
        //         return false;
        //     }
        //     solver.solve(desc.RHS());
        //     if (solver.info() != Eigen::Success)
        //     {
        //         // solving failed
        //         return false;
        //     }
        // }
        const Vector &Solution() const { return x; }
    };

} // Solver

#endif