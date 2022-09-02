#include <iostream>
#include <string>
#include "../../../ModelGenerator/ModelGenerator.h"
#include "../../../StreamOutput/StreamOutput.h"

/**
 * @brief Test of the method ModelGenerator::FileParser::KfileParser::parse_section_element()
 */
int main(int argc, char **argv)
{

std::ofstream f{"musor.txt"};
f.close();


    ModelGenerator::FileParser::KfileParser parser;
    try
    {
        parser = ModelGenerator::FileParser::KfileParser("element_section.k");
    }
    catch (std::runtime_error &e)
    {
        std::cout << "Fail ";
        std::cout << "\nReturn " << '\n'
                  << e.what() << std::flush;
        return -1;
    }

    // the file is opened

    auto elements = parser.parse_section_element();

    using namespace ModelDescriptor;

    if (elements.size() != 38)
    {
        std::cout << "Fail ";
        std::cout << "\nReturn " << '\n'
                  << elements;
        return -1;
    }

    if (elements[10](0) != 12 || elements[10](1) != 20 || elements[10](2) != 21)
    {
        std::cout << "Fail ";
        std::cout << "\nReturn " << '\n'
                  << elements;
        return -1;
    }

    std::cout << "Pass ";

    return 0;
}