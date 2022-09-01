#ifndef STREAMOUTPUT_H
#define STREAMOUTPUT_H

#include <iostream>
#include <iomanip>

#include "../ModelGenerator/ModelDescriptor.h"
#include "../eigen/Eigen/SparseCore"

namespace ModelDescriptor
{
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::MaterialPropDesc& desc);

    std::ostream& operator<<(std::ostream& o, const Eigen::Vector2d& v);

    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::Node& node);

    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::Points& p);

} // ModelDescriptor
#endif