#include <iostream>
#include "../../../ModelGenerator/ModelGenerator.h"
#include "../../../StreamOutput/StreamOutput.h"

/**
 * @brief Test of the class ModelDescriptor::MaterialPropDesc ctor
 */
int main(int argc, char **argv)
{
    auto desc{ModelGenerator::GridGenerator()};

 //   ModelDescriptor::GridDesc desc{points, elements};

    if (desc.elements[0](0) == ModelDescriptor::Point{0.0, 0.0} &&
        desc.elements[0](1) == ModelDescriptor::Point{1.0, 0.0} &&
        desc.elements[0](2) == ModelDescriptor::Point{0.0, 1.0})
    {
        std::cout << "Pass ";
        std::cout << "\nReturn " << '\n';
        return 0;
    }
    else
    {
        std::cerr << "Fail ";
        std::cerr << "\nReturn " << '\n';
        return -1;
    }

    return -1;
}