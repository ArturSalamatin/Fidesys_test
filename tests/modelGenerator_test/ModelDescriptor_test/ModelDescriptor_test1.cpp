#include <iostream>
#include "../../../ModelGenerator/ModelDescriptor.h"
#include "../../../StreamOutput/StreamOutput.h"

/**
 * @brief Test of the class ModelDescriptor::MaterialPropDesc ctor
 */
int main(int argc, char** argv) 
{
    
    ModelDescriptor::MaterialPropDesc desc{2E11, 0.3};
 
    if(desc.E == 2E11 && desc.mu == 0.3)
    {
        std::cout << "Pass ";
        std::cout  << "\nReturn " << '\n' << desc;
        return 0;
    }
    else
    {
        std::cerr << "Fail ";
        std::cerr  << "\nReturn " << '\n' << desc;
        return -1;
    }

    return -1;
}