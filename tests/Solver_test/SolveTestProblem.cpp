#include <iostream>
#include <string>

#include "../../ModelGenerator/ModelGenerator.h"
#include "../../Solver/Solver.h"

/**
 * @brief Test the Solver with 1 element
 */
int main(int argc, char **argv)
{
    auto gridDesc{ModelGenerator::MeshDescriptorFromFile("data\\task_mesh_fine.k")};    // get mesh from file
    ModelDescriptor::MaterialPropDesc props{ModelGenerator::MaterialPropDescDefault()}; // some prescribed properties
    TLLE::LagrangeElement::MaterialMatrix c{props};

    Solver::ProblemDesc<TLLE::LNC, TLLE::DOF> problem{gridDesc, props};

    problem.set_A();
    problem.set_b(0.15, 1E6); // send thickness and force to compute the rhs
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

    Solver::SolutionOutput<3, 2> outputter{problem, solver.Solution(), c};

    outputter.print("data\\solution.csv");

    std::cout << "Pass \n";
    std::cout << solver.Solution() << std::endl;
    return 0;
}