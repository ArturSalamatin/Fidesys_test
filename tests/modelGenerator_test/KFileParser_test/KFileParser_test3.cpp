#include <iostream>
#include <string>
#include "../../../ModelGenerator/ModelGenerator.h"
#include "../../../StreamOutput/StreamOutput.h"

/**
 * @brief Test of the method ModelGenerator::FileParser::KfileParser::parse_section_element()
 */
int main(int argc, char **argv)
{
    try
    {
        ModelGenerator::FileParser::KfileParser parser{"data\\element_section.k"};
    }
    catch (const std::exception& e)
    {
        std::cerr << "Fail ";
        std::cerr << "\nReturn " << '\n'
                  << e.what() << std::flush;
        return -1;
    }

    ModelGenerator::FileParser::KfileParser parser{"data\\element_section.k"};
    // the file is opened

    ModelDescriptor::ElementsDescWithIdContainer elements;

    try
    {
        elements = parser.parse_section_element();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Fail ";
        std::cerr << "\nReturn " << '\n'
                  << e.what() << std::flush;

    }

    using namespace ModelDescriptor; // for overloaded operator<<

    if (elements.size() != 38)
    {
        std::cerr << "Fail ";
        std::cerr << "\nReturn " << '\n'
                  << elements;
        return -1;
    }

size_t id = 9;
    if (
        elements[id].e(0) != 21 || 
        elements[id].e(1) != 12 || 
        elements[id].e(2) != 20)
    {
        std::cerr << "Fail ";
        std::cerr << "\nReturn " << '\n'
                  << elements;
        return -1;
    }

    std::cout << "Pass ";

    return 0;
}