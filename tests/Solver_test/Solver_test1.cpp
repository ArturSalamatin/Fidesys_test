#include <iostream>
#include <string>

#include "../../ModelGenerator/ModelGenerator.h"
#include "../../Solver/Solver.h"

/**
 * @brief Test the Solver with 1 element
 */
int main(int argc, char **argv)
{
    auto gridDesc{ModelGenerator::GridGenerator()};

    ModelDescriptor::MaterialPropDesc props{1.0, 0.0}; // very simple properties
    TLLE::LagrangeElement::MaterialMatrix c{props};

    Solver::ProblemDesc<TLLE::LNC, TLLE::DOF> problem{gridDesc, props};

    problem.set_A();
    problem.set_b();

    std::cout << problem.RHS() << '\n';
    std::cout << problem.Matrix() << '\n';

    Solver::Solver solver;
    try
    {
        bool f = solver.solve<TLLE::LNC, TLLE::DOF>(problem);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fail ";
        std::cerr << e.what() << '\n';
        return -1;
    }
    
    for(auto v : solver.Solution())
    {
        if(v != 0.0)
        {
        std::cerr << "Fail ";
        std::cerr << "Solution is wrong." << '\n';
        return -1;

        }
    }

    std::cout << "Pass " << std::flush;
    return 0;
}