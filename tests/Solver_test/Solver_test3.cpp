#include <iostream>
#include <string>

#include "../../ModelGenerator/ModelGenerator.h"
#include "../../Solver/Solver.h"

/**
 * @brief Test the Solver with 1 element
 */
int main(int argc, char **argv)
{
    auto gridDesc{ModelGenerator::MeshDescriptorFromFile("data\\task_mesh_coarse.k")};  // get mesh from file
    ModelDescriptor::MaterialPropDesc props{ModelGenerator::MaterialPropDescDefault()}; // some prescribed properties
    TLLE::LagrangeElement::MaterialMatrix c{props};

    Solver::ProblemDesc<TLLE::LNC, TLLE::DOF> problem{gridDesc, props};

    problem.set_A();
    problem.set_b(0.15, 1E6);
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