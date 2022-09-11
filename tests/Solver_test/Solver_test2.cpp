#include <iostream>
#include <string>

#include "../../ModelGenerator/ModelGenerator.h"
#include "../../Solver/Solver.h"

double tol = 1E-14;

Eigen::Vector2d getDisplacement(size_t id, const Solver::Vector &sol)
{
    return Eigen::Vector2d{sol(2 * id), sol(2 * id + 1)};
}

bool comp(double val, double control = 0.0)
{
    return std::abs(val - control) < tol;
}

/**
 * @brief Test the Solver with 2 elements filling a square
 */
int main(int argc, char **argv)
{
    ModelDescriptor::GridDesc gridDesc{ModelGenerator::GridGenerator2()};

    ModelDescriptor::MaterialPropDesc props{1.0, 0.0}; // very simple properties
    TLLE::LagrangeElement::MaterialMatrix c{props};

    Solver::ProblemDesc<TLLE::LNC, TLLE::DOF> problem{gridDesc, props};

    problem.set_A();
    problem.set_b();
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

        std::cout << stress << std::endl
                  << std::endl;

        if (std::abs(stress(0) - 1.0) > tol || std::abs(stress(1)) > tol || std::abs(stress(2)) > tol)
        {
            std::cerr << "Fail \nWith stress components:\n";
            std::cerr << stress << std::endl;
        }
    }

    if (comp(s(0)) &&
        comp(s(1)) &&
        comp(s(2), 1.0) &&
        comp(s(3)) &&
        comp(s(4)) &&
        comp(s(5)) &&
        comp(s(6), 1.0) &&
        comp(s(7)))
    {
        std::cout << "Pass \n";
        std::cout << solver.Solution() << std::endl;
        return 0;
    }
    else
    {
        std::cerr << "Fail \n";
        std::cerr << solver.Solution() << std::endl;
        return -1;
    }

    return 0;
}