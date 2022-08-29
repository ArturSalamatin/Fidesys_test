#ifndef STREAMOUTPUT_H
#define STREAMOUTPUT_H

#include <iostream>
#include <iomanip>

#include "../ModelGenerator/ModelDescriptor.h"

namespace ModelDescriptor
{
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::MaterialPropDesc& desc);
} // ModelDescriptor
#endif