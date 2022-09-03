#include <iostream>
#include <string>
// #include "../../../ModelGenerator/ModelDescriptor.h"
#include "../../../ModelGenerator/ModelGenerator.h"
#include "../../../StreamOutput/StreamOutput.h"

/**
 * @brief Test of the method ModelGenerator::FileParser::KfileParser::parse_section_node()
 */
int main(int argc, char **argv)
{
    try
    {
        ModelGenerator::FileParser::KfileParser parser{"node_section.k"};
    }
    catch (std::runtime_error &e)
    {
        std::cerr << "Fail ";
        std::cerr << "\nReturn " << '\n'
                  << e.what() << std::flush;
        return -1;
    }

    ModelGenerator::FileParser::KfileParser parser{"node_section.k"};
    // the file is opened

    ModelDescriptor::Points points;
    try
    {
        points = parser.parse_section_node();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fail ";
        std::cerr << "\nReturn " << '\n';
        std::cerr << e.what() << '\n';
    }

    using namespace ModelDescriptor;

    if (points.size() != 28)
    {
        std::cerr << "Fail ";
        std::cerr << "\nReturn " << '\n'
                  << points;
        return -1;
    }

    if (points[28](0) != 0.0604836 || points[28](1) != 0.0676566 || points[4](0) != 0.0 || points[4](1) != 0.25)
    {
        std::cerr << "Fail ";
        std::cerr << "\nReturn " << '\n'
                  << points;
        return -1;
    }

    std::cout << "Pass ";

    return 0;
}