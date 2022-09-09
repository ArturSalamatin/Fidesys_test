#ifndef NDEBUG
#include <cassert>
#else
#undef NDEBUG
#include <cassert>
#define NDEBUG
#endif

#include "ModelDescriptor.h"

namespace ModelDescriptor
{

    MaterialPropDesc::MaterialPropDesc(double E, double mu) noexcept : E{E}, mu{mu}
    {
        assert((E > 0.0) && "Young modulus must not be negative!");
        assert((mu > -1.0) && "Poisson's ratio must be greater than -1!");
        assert((mu < 0.5) && "Poisson's ratio must be less than 0.5!");
    }

    ElementDescWithID::ElementDescWithID(unsigned int id, const ElementDesc &e) noexcept : id{id}, e{e}
    {
        //    std::sort(this->e.begin(), this->e.end()); // this operation might ruin the clockwise direction of nodes
    }

    GridDesc::GridDesc(const PointContainer &points, const ElementsDescContainer elements)
        : points{points}, elementsDesc{elements}
    {
    }
} // ModelDescriptor