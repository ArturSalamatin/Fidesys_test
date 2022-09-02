#ifndef STREAMOUTPUT_H
#define STREAMOUTPUT_H

#include <iostream>
#include <iomanip>

#include "../ModelGenerator/ModelDescriptor.h"
//#include "../eigen/Eigen/SparseCore"

namespace ModelDescriptor
{
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::MaterialPropDesc& desc);

    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::Point2D& v);
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::Node& node);
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::Points& p);


    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::Element2D& v);
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::Element& e);
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::Elements& e);
} // ModelDescriptor
#endif