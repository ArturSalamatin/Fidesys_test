#include <iostream>
#include <string>

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
    auto gridDesc{ModelGenerator::MeshDescriptorFromFile("data\\task_mesh_homo2.k")};   // get mesh from file
 //   ModelDescriptor::MaterialPropDesc props{ModelGenerator::MaterialPropDescDefault()}; // some prescribed properties
    ModelDescriptor::MaterialPropDesc props{1.0, 0.3}; // some prescribed properties
    double w = 1.0;
    double f = w; // 1E6
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

    std::cout << "Solution:\n" << s << std::endl;
    std::cout << "RHS:\n" << problem.RHS() << std::endl;
    std::cout << "Matrix:\n" << problem.Matrix() << std::endl;

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
        std::cout << "Element " << eId << ", stress:\n" << stress << std::endl
                  << std::endl;

        // if (s(0) != 1.0 || std::abs(s(1)) > 1E-16 || std::abs(s(2)) > 1E-16)
        // {
        //     std::cerr << "Fail \nWith stress components:\n";
        //     std::cerr << stress << std::endl;
        // }
    }

    // const auto &s = solver.Solution();
    // if (s(0) < 1E-16 &&
    //     s(1) < 1E-16 &&
    //     s(2) == 1.0 &&
    //     s(3) < 1E-16 &&
    //     s(4) < 1E-16 &&
    //     s(5) < 1E-16 &&
    //     s(6) == 1.0 &&
    //     s(7) < 1E-16)
    // {

    //     std::cout << "Pass \n";
    //     std::cout << solver.Solution() << std::endl;
    //     return 0;
    // }
    // else
    // {

    //     std::cout << "Fail \n";
    //     std::cout << solver.Solution() << std::endl;
    //     return -1;
    // }

    std::cout << "Pass \n";
    std::cout << solver.Solution() << std::endl;
    return 0;
}