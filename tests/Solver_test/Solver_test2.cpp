#include <iostream>
#include <string>

#include "../test_methods.h"
#include "../../ModelGenerator/ModelGenerator.h"
#include "../../Solver/Solver.h"

/**
 * @brief Test the Solver with 2 elements filling a square
 */
int main(int argc, char **argv)
{
    using namespace TestSpace;

    double f = 1E6;
    double E = 1E11;
    double mu = 0.0;
    double w = 1.0;
    double h = 20.0;

    ModelDescriptor::GridDesc gridDesc{ModelGenerator::GridGenerator2(w, h)};

    ModelDescriptor::MaterialPropDesc props{E, mu}; // very simple properties
    TLLE::LagrangeElement::MaterialMatrix c{props};

    Solver::ProblemDesc<TLLE::LNC, TLLE::DOF> problem{gridDesc, props};

    problem.set_A();
    problem.set_b(w, f);
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

        if (!comp(stress(0), f) || !comp(stress(1)) || !comp(stress(2)))
        {
            std::cerr << "Fail\n";
            std::cerr << "ElementId: " << eId << "; Stress:\n"
                      << stress << std::endl
                      << std::endl;
        }
        
        TLLE::Strain strain;
        strain = el.getStrain(v1, v2, v3);
        if (!comp(strain(0), f/E) || !comp(strain(1), -mu*f/E) || !comp(strain(2)))
        {
            std::cerr << "Fail\n";
            std::cerr << "ElementId: " << eId << "; Strain:\n"
                      << strain << std::endl
                      << std::endl;
        }
    }

    if (comp(s(0)) &&
        comp(s(1)) &&
        comp(s(2), f / E * w) &&
        comp(s(3)) &&
        comp(s(4)) &&
        comp(s(5), -mu * h * f / E) &&
        comp(s(6), f / E * w) &&
        comp(s(7), -mu * h * f / E))
    {
        std::cout << "Pass \n"
                  << std::endl;
        //       std::cout << solver.Solution() << std::endl;
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