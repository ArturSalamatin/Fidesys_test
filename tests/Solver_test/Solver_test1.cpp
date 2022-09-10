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

    std::cout << "Pass ";
    return 0;
}