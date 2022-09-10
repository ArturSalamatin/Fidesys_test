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

    GridDesc::GridDesc(const PointWithIdContainer &Points, const ElementsDescWithIdContainer Elements) noexcept
    {
        pointCodes.reserve(Points.size());
        for (const auto &[id, p] : Points)
        {
            pointCodes.push_back(id);
            reversePointCodes.insert({id, pointCodes.size()-1});
            points.push_back(p);
        }

 //       std::vector<unsigned int> elementsCodes;
//        elementsCodes.reserve(Elements.size());
        for (const auto &[id, e] : Elements)
        {
 //           elementsCodes.push_back(id);
            elementsDesc.emplace_back(reversePointCodes[e(0)], reversePointCodes[e(1)], reversePointCodes[e(2)]);
            // const auto& eD = elementsDesc.back();
            elements.emplace_back(points[reversePointCodes[e(0)]], points[reversePointCodes[e(1)]], points[reversePointCodes[e(2)]]);
        }
    }
} // ModelDescriptor