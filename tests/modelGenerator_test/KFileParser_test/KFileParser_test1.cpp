#include <iostream>
#include <string>
#include "../../../ModelGenerator/ModelGenerator.h"
#include "../../../StreamOutput/StreamOutput.h"

/**
 * @brief Test of the class ModelGenerator::FileParser::KfileParser string parsing
 */
int main(int argc, char** argv) {
    

    std::string str{"     305               0               0               0       0       0"};

    auto out{ModelGenerator::FileParser::KfileParser::parse_node(str)};

    if(out.id != 305)
    {
        std::cerr << "Fail ";
        std::cerr  << "\nReturn " << '\n' << out;
        return -1;
    }
    if(out.p(0) != 0.0 || out.p(1) != 0.0)
    {
        std::cerr << "Fail ";
        std::cerr  << "\nReturn " << '\n' << out;
        return -1;
    }

    str = {"     68       0.0221384        0.071282               0       0       0"};

    out = ModelGenerator::FileParser::KfileParser::parse_node(str);

    if(out.id != 68)
    {
        std::cerr << "Fail ";
        std::cerr  << "\nReturn " << '\n' << out;
        return -1;
    }
    if(out.p(0) != 0.0221384 || out.p(1) != 0.071282)
    {
        std::cerr << "Fail ";
        std::cerr  << "\nReturn " << '\n' << out;
        return -1;
    }

    std::cout << "Pass " << std::flush;

    return 0;
}