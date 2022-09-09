#ifndef STREAMOUTPUT_H
#define STREAMOUTPUT_H

#include <iostream>
#include <iomanip>

#include "../ModelGenerator/ModelDescriptor.h"
//#include "../eigen/Eigen/SparseCore"

namespace ModelDescriptor
{
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::MaterialPropDesc& desc);

    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::Point& v);
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::PointWithID& node);
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::PointContainer& p);
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::PointWithIdContainer& p);


    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::ElementDesc& v);
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::ElementDescWithID& e);
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::ElementsDescContainer& e);
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::ElementsDescWithIdContainer& e);
} // ModelDescriptor
#endif