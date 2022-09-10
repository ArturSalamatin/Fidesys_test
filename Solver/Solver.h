#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <unordered_map>
// #include <omp.h>
#include "../eigen/Eigen/SparseCore"
#include "../eigen/Eigen/OrderingMethods"
#include "../eigen/Eigen/SparseLU"
// #include "../eigen/Eigen/SparseQR"

//#include "../ModelGenerator/ModelDescriptor.h"
#include "../LagrangeElements/LagrangeElements.h"

namespace Solver
{
    using SparseMatrix = Eigen::SparseMatrix<double, Eigen::ColMajor>;
    using Vector = Eigen::VectorXd;
    using MatrixSolver = Eigen::SparseLU<SparseMatrix, Eigen::COLAMDOrdering<int>>;

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

            // apply boundary conditions
            // Ux = 0 at x = 0
            // Uy = 0 at y = 0
            for (size_t node = 0; node < gridDesc.PointsCount(); ++node)
            {
                const auto &p = gridDesc.points[node];
                if (p.x() == 0)
                {
                    // Ux = 0 at x = 0
                    for (size_t coef = coefficients.size(); coef > 0; --coef)
                    {
                        if (coefficients[coef - 1].row() == node * dof)
                            coefficients.erase(coefficients.begin() + coef - 1);
                    }
                    coefficients.emplace_back(node * dof, node * dof, 1);
                }
                if (p.y() == 0)
                {
                    // Uy = 0 at y = 0
                    for (size_t coef = coefficients.size(); coef > 0; --coef)
                    {
                        if (coefficients[coef - 1].row() == node * dof + 1)
                            coefficients.erase(coefficients.begin() + coef - 1);
                    }
                    coefficients.emplace_back(node * dof + 1, node * dof + 1, 1);
                }
            }

            A = SparseMatrix(problem_size, problem_size);
            A.setFromTriplets(coefficients.begin(), coefficients.end());
            A.makeCompressed();
        }
        void set_b() noexcept
        {
            b = Vector(problem_size);
            for (auto &it : b)
                it = 0.0;

            double w = 1.0;
            double f = 1.0;
            for (size_t eId = 0; eId < gridDesc.ElementsCount(); ++eId)
            {
                const auto &p1Id = gridDesc.elementsDesc[eId](0);
                const auto &p2Id = gridDesc.elementsDesc[eId](1);
                const auto &p3Id = gridDesc.elementsDesc[eId](2);

                const auto &p1 = gridDesc.points[p1Id];
                const auto &p2 = gridDesc.points[p2Id];
                const auto &p3 = gridDesc.points[p3Id];

                double edge;
                if (p1.x() == w && p2.x() == w)
                {
                    edge = std::abs(p1.y() - p2.y());
                    b(p1Id * dof) += 0.5 * edge * f;
                    b(p2Id * dof) += 0.5 * edge * f;
                }
                if (p1.x() == w && p3.x() == w)
                {
                    edge = std::abs(p1.y() - p3.y());
                    b(p1Id * dof) += 0.5 * edge * f;
                    b(p3Id * dof) += 0.5 * edge * f;
                }
                if (p3.x() == w && p2.x() == w)
                {
                    edge = std::abs(p3.y() - p2.y());
                    b(p3Id * dof) += 0.5 * edge * f;
                    b(p2Id * dof) += 0.5 * edge * f;
                }
            }
        }
    };

    /**
     * @brief Solver is responsible for solving a problem Ax=b
     * with specified matrix A and rhs b
     *
     */

    class Solver
    {
    protected:
        Vector x;
        MatrixSolver solver;

    public:
        //    Solver() noexcept;
        template <unsigned char lnc, unsigned char dof>
        bool solve(const ProblemDesc<lnc, dof> &desc)
        {
            auto const& A = desc.Matrix();
        //    solver.analyzePattern(desc.Matrix());
        //    solver.factorize(A); 
            solver.compute(desc.Matrix());
            if (solver.info() != Eigen::Success)
            {
                // decomposition failed
                throw std::runtime_error(solver.lastErrorMessage());
                return false;
            }
            x = solver.solve(desc.RHS());
            if (solver.info() != Eigen::Success)
            {
                // solving failed
                return false;
            }
            return true;
        }
        const Vector &Solution() const { return x; }
    };

} // Solver

#endif