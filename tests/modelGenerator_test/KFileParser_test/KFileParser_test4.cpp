#include <iostream>
#include <string>
#include "../../../ModelGenerator/ModelGenerator.h"
#include "../../../StreamOutput/StreamOutput.h"

/**
 * @brief Test of the method ModelGenerator::MeshDescriptorFromFile()
 */
int main(int argc, char **argv)
{
    ModelDescriptor::GridDesc meshDesc;
    try
    {
        meshDesc = ModelGenerator::MeshDescriptorFromFile("data\\task_mesh_coarse.k");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fail ";
        std::cerr << "\nReturn " << '\n'
                  << e.what() << std::flush;
        return -1;
    }

    std::cout 
    << "Elements count: " << meshDesc.elementsDesc.size() << '\n'
    << "Points count:   " << meshDesc.points.size() << '\n';


    using namespace ModelDescriptor; // for overloaded operator<<

    if (meshDesc.elementsDesc.size() != 38)
    {
        std::cerr << "Fail "
        << "\nWrong elements count";
        std::cerr << "\nReturn " << '\n'
                  << meshDesc.elementsDesc;
        return -1;
    }

    if (meshDesc.points.size() != 28)
    {
        std::cerr << "Fail "
        << "\nWrong points count";
        std::cerr << "\nReturn " << '\n'
                  << meshDesc.points;
        return -1;
    }

    if (meshDesc.points[28](0) != 0.0604836 || meshDesc.points[28](1) != 0.0676566 || meshDesc.points[4](0) != 0.0 || meshDesc.points[4](1) != 0.25)
    {
        std::cerr << "Fail "
        << "\nWrong elemnt nodes coordinates";
        std::cerr << "\nReturn " << '\n'
                  << meshDesc.points;
        return -1;
    }

    if (meshDesc.elementsDesc[10](0) != 21 || meshDesc.elementsDesc[10](1) != 12 || meshDesc.elementsDesc[10](2) != 20)
    {
        std::cerr << "Fail "
        << "\nWrong local nodes ids";
        std::cerr << "\nReturn " << '\n'
                  << meshDesc.elementsDesc;
        return -1;
    }

    std::cout << "Pass ";

    return 0;
}