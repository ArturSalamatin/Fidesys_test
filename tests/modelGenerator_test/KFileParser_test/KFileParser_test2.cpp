#include <iostream>
#include <string>
#include "../../../ModelGenerator/ModelGenerator.h"
#include "../../../StreamOutput/StreamOutput.h"

/**
 * @brief Test of the method ModelGenerator::FileParser::KfileParser::parse_section_node()
 */
int main(int argc, char **argv)
{
    try
    {
        ModelGenerator::FileParser::KfileParser parser{"data\\node_section.k"};
    }
    catch (std::runtime_error &e)
    {
        std::cerr << "Fail ";
        std::cerr << "\nReturn " << '\n'
                  << e.what() << std::flush;
        return -1;
    }

    ModelGenerator::FileParser::KfileParser parser{"data\\node_section.k"};
    // the file is opened

    ModelDescriptor::PointWithIdContainer points;
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

// size_t id1 = 28-1;
// size_t id2 = 4-1;
//     if (points[id1].p(0) != 0.0604836 || points[id1].p(1) != 0.0676566 || points[id2].p(0) != 0.0 || points[id2].p(1) != 0.25)
//     {
//         std::cerr << "Fail ";
//         std::cerr << "\nReturn " << '\n'
//                   << points;
//         return -1;
//     }

    std::cout << "Pass ";

    return 0;
}