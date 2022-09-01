#include <iostream>
#include <string>
// #include "../../../ModelGenerator/ModelDescriptor.h"
#include "../../../ModelGenerator/ModelGenerator.h"
#include "../../../StreamOutput/StreamOutput.h"

/**
 * @brief Test of the class ModelDescriptor::MaterialPropDesc ctor
 */
int main(int argc, char** argv) {
    
    ModelGenerator::FileParser::KfileParser parser;
try
{
    parser = ModelGenerator::FileParser::KfileParser("d:\\Lessons\\MyPrograms\\VisualStudio\\C++\\Fidesys_test\\tests\\modelGenerator_test\\data\\task_mesh_coarse copy.k");
}
catch(std::runtime_error& e)
{
        std::cout << "Fail ";
        std::cout  << "\nReturn " << '\n' << e.what() << std::flush;
        return -1;
}

// the file is opened

auto points = parser.parse_section_node();

using namespace ModelDescriptor;

    if(points.size() != 28)
    {
        std::cout << "Fail ";
        std::cout  << "\nReturn " << '\n' << points;
        return -1;
    }

    if(points[28](0) != 0.0604836 || points[28](1) != 0.0676566
        || points[4](0) != 0.0 || points[4](1) != 0.25)
    {
        std::cout << "Fail ";
        std::cout  << "\nReturn " << '\n' << points;
        return -1;
    }

    std::cout << "Pass ";

    return 0;
}