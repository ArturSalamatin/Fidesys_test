#ifndef MODELDESCRIPTOR_H
#define MODELDESCRIPTOR_H

#ifndef NDEBUG
#include <cassert>
#else
#undef NDEBUG
#include <cassert>
#define NDEBUG
#endif

namespace ModelDescriptor
{
    /**
     * @brief Structure describing material properties of the body
     * 
     */
    struct MaterialPropDesc
    {
        /**
         * @brief Ctor for a new MaterialPropDesc object
         * 
         * @param E Young modulus, Pa
         * @param mu Poisson's ratio, -
         */
        MaterialPropDesc(double E, double mu) :
            E{E}, mu{mu}
        {
        //    assert((E < 0.0) && "Young modulus must not be negative!");
        //    assert(("Poisson's ratio must be greater than -1!", mu < -1.0));
        //    assert((mu > 0.5) && "Poisson's ratio must be less than 0.5!");
        }

        double E;  /**< Young modulus, Pa */
        double mu; /**<  Poisson's ratio, - */
    };



} // ModelDescriptor
#endif