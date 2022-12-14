#include <iostream>
#include <string>

#include "../../ModelGenerator/ModelDescriptor.h"
#include "../../ModelGenerator/ModelGenerator.h"
#include "../../LagrangeElements/LagrangeElements.h"

/**
 * @brief Test of the stiffness matrix construction, class TTLE::LagrangeElement
 */
int main(int argc, char **argv)
{
    auto gridDesc{ModelGenerator::GridGenerator()};

    ModelDescriptor::MaterialPropDesc props{1.0, 0.0}; // very simple properties
    TLLE::LagrangeElement::MaterialMatrix c{props};

    TLLE::LagrangeElement lagrElem{gridDesc.elements[0], props, c};

    TLLE::LagrangeElement::StiffnessMatrix K;
    double area{0.5};

    K << 1.5, 0.5, 0.5, 1.5;
    if (area * K != lagrElem.K[0][0])
    {
        std::cerr << "Fail "
                  << "Wrong stiffness matrix K[0][0]"
                  << std::flush;
        return -1;
    }

    K << 1.0, 0.0, 0.0, 0.5;
    if (area * K != lagrElem.K[1][1])
    {
        std::cerr << "Fail "
                  << "Wrong stiffness matrix K[1][1]"
                  << std::flush;
        return -1;
    }

    K << -1.0, -0.5, 0.0, -0.5;
    if (area * K != lagrElem.K[0][1])
    {
        std::cerr << "Fail "
                  << "Wrong stiffness matrix K[0][1]"
                  << std::flush;
        return -1;
    }

    // symmetry constraints on stiffness matrix K
    if (lagrElem.K[1][0].transpose() != lagrElem.K[0][1])
    {
        std::cerr << "Fail "
                  << "Wrong stiffness matrix K[0][1] and K[1][0]. They are not transpose-equal"
                  << std::flush;
        return -1;
    }

    if (lagrElem.K[2][0].transpose() != lagrElem.K[0][2])
    {
        std::cerr << "Fail "
                  << "Wrong stiffness matrix K[0][2] and K[2][0]. They are not transpose-equal"
                  << std::flush;
        return -1;
    }

    if (lagrElem.K[1][2].transpose() != lagrElem.K[2][1])
    {
        std::cerr << "Fail "
                  << "Wrong stiffness matrix K[2][1] and K[1][2]. They are not transpose-equal"
                  << std::flush;
        return -1;
    }

    std::cout << "Pass ";
    return 0;
}