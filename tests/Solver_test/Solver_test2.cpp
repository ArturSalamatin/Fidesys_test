#include <iostream>
#include <string>

#include "../../ModelGenerator/ModelGenerator.h"
#include "../../Solver/Solver.h"

/**
 * @brief Test the Solver with 1 element
 */
int main(int argc, char **argv)
{

    ModelGenerator::FileParser::KfileParser parser{"data\\task_mesh_homo2.k"};
    parser.parse();
    ModelDescriptor::GridDesc gridDesc{parser.p, parser.e};

    ModelDescriptor::MaterialPropDesc props{1.0, 0.0}; // very simple properties
    TLLE::LagrangeElement::MaterialMatrix c{props};

    Solver::ProblemDesc<TLLE::LNC, TLLE::DOF> problem{gridDesc, props};

    problem.set_A();

    std::cout << problem.Matrix();

    std::cout << "Pass ";
    return 0;
}