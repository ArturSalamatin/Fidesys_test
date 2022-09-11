#include <iostream>
#include <string>

#include "../../StreamOutput/StreamOutput.h"
#include "../../ModelGenerator/ModelGenerator.h"
#include "../../Solver/Solver.h"

double tol = 1E-11;

bool comp(double val, double control = 0.0)
{
    if (control == 0.0)
        return std::abs(val) < tol;
    else
        return std::abs(control - val ) < tol;
}

Eigen::Vector2d getDisplacement(size_t id, const Solver::Vector &sol)
{
    return Eigen::Vector2d{sol(2 * id), sol(2 * id + 1)};
}

/**
 * @brief Test the Solver with 1 element
 */
int main(int argc, char **argv)
{
    double w = 0.15;
    double h = 0.25;
    double f = 1E6; // 1E6

    double E = 2E11;
    double mu = 0.3;

    auto gridDesc{ModelGenerator::MeshDescriptorFromFile("data\\task_mesh_homo.k")}; // get mesh from file
    ModelDescriptor::MaterialPropDesc props{E, mu}; // some prescribed properties

    TLLE::LagrangeElement::MaterialMatrix c{props};

    Solver::ProblemDesc<TLLE::LNC, TLLE::DOF> problem{gridDesc, props};

    problem.set_A();
    problem.set_b(w, f); // send thickness and force to compute the rhs
    Solver::Solver solver;

    try
    {
        solver.solve<TLLE::LNC, TLLE::DOF>(problem);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fail ";
        std::cerr << e.what() << '\n';

        std::cerr << problem.RHS() << '\n';
        std::cerr << problem.Matrix() << '\n';
        return -1;
    }

    const auto &s = solver.Solution();

    // loop through all nodes
    for (size_t pId = 0; pId < gridDesc.PointsCount(); ++pId)
    {
        const auto &p = gridDesc.points[pId];
        double x = p.x(), y = p.y();
        double u = x * f / E;
        double v = -mu * y * f / E;
        auto v1 = getDisplacement(pId, s);

        if (!comp(v1(0), u) ||
            !comp(v1(1), v))
        {
            std::cerr << "Fail: wrong displacement\n" << v1(0) << "  " << u << '\n' << v1(1) << "  " << v << std::endl;
        }
    }

    // loop through all elements
    for (size_t eId = 0; eId < gridDesc.ElementsCount(); ++eId)
    {
        const auto &p1Id = gridDesc.elementsDesc[eId](0);
        const auto &p2Id = gridDesc.elementsDesc[eId](1);
        const auto &p3Id = gridDesc.elementsDesc[eId](2);

        const auto &p1 = gridDesc.points[p1Id];
        const auto &p2 = gridDesc.points[p2Id];
        const auto &p3 = gridDesc.points[p3Id];

        const auto &el = problem.lagrElems[eId];

        TLLE::Stress stress;
        auto v1 = getDisplacement(p1Id, s);
        auto v2 = getDisplacement(p2Id, s);
        auto v3 = getDisplacement(p3Id, s);
        stress = el.getStress(v1, v2, v3, c);
        std::cout << "Element " << eId << ", stress:\n"
                  << stress << std::endl;

        // std:: cout << std::abs(stress(0) - f) << ' ' << std::abs(stress(1)) << ' ' << std::abs(stress(2)) << std::endl;

        if (!comp(stress(0), f) ||
            !comp(stress(1)) ||
            !comp(stress(2)))
        {
            std::cerr << "Fail " << std::endl;
        }

        TLLE::Strain strain;
        strain = el.getStrain(v1, v2, v3);
        std::cout << "Element " << eId << ", strain:\n"
                  << strain << std::endl
                  << std::endl;

        if (!comp(strain(0), f / E) ||
            !comp(strain(1), mu * f / E) ||
            !comp(strain(2)))
        {
            std::cerr << "Fail " << std::endl;
        }
    }

    std::cout << "Pass \n";
    return 0;
}