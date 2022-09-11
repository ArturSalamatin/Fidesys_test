#include <iostream>
#include <string>

#include "../../StreamOutput/StreamOutput.h"
#include "../../ModelGenerator/ModelGenerator.h"
#include "../../Solver/Solver.h"

Eigen::Vector2d getDisplacement(size_t id, const Solver::Vector &sol)
{
    return Eigen::Vector2d{sol(2 * id), sol(2 * id + 1)};
}

/**
 * @brief Test the Solver with 1 element
 */
int main(int argc, char **argv)
{
    double w = 2.0;
    double h = 5.0;
    double f = 1; // 1E6
    double tol = 1E-14;

    double E = 1.0;
    double mu = 0.3;

    auto gridDesc{ModelGenerator::GridGenerator2(w, h)}; // get mesh from file
    {
        using namespace ModelDescriptor;

        std::cout << gridDesc.points << std::endl;
    }
    //   ModelDescriptor::MaterialPropDesc props{ModelGenerator::MaterialPropDescDefault()}; // some prescribed properties
    ModelDescriptor::MaterialPropDesc props{E, mu}; // some prescribed properties

    TLLE::LagrangeElement::MaterialMatrix c{props};

    Solver::ProblemDesc<TLLE::LNC, TLLE::DOF> problem{gridDesc, props};

    problem.set_A();
    problem.set_b(w, f); // send thickness and force to compute the rhs
    Solver::Solver solver;

    try
    {
        bool f = solver.solve<TLLE::LNC, TLLE::DOF>(problem);
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

    std::cout << "Solution:\n"
              << s << std::endl;
    std::cout << "RHS:\n"
              << problem.RHS() << std::endl;
    std::cout << "Matrix:\n"
              << problem.Matrix() << std::endl;

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
                  << stress << std::endl
                  << std::endl;

        if (std::abs(stress(0) - f) > tol ||
            std::abs(stress(1)) > tol ||
            std::abs(stress(2)) > tol)
        {
            std::cerr << "Fail " << std::endl;
        }

        TLLE::Strain strain;
        strain = el.getStrain(v1, v2, v3);
        std::cout << "Element " << eId << ", strain:\n"
                  << strain << std::endl
                  << std::endl;

        if (std::abs(strain(0) - f/(E)) > tol ||
            std::abs(strain(1) + mu*f/(E)) > tol ||
            std::abs(strain(2)) > tol)
        {
            std::cerr << "Fail " << std::endl;
        }
    }

    std::cout << "Pass \n";
    return 0;
}