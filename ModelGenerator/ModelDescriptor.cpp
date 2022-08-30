#ifndef NDEBUG
#include <cassert>
#else
#undef NDEBUG
#include <cassert>
#define NDEBUG
#endif

#include "ModelDescriptor.h"

ModelDescriptor::MaterialPropDesc::MaterialPropDesc(double E, double mu) noexcept : E{E}, mu{mu}
{
    //    assert((E < 0.0) && "Young modulus must not be negative!");
    //    assert(("Poisson's ratio must be greater than -1!", mu < -1.0));
    //    assert((mu > 0.5) && "Poisson's ratio must be less than 0.5!");
}