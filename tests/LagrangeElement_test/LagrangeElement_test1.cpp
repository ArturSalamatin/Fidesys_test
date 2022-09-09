#include <iostream>
#include <string>

#include "../../ModelGenerator/ModelDescriptor.h"
#include "../../ModelGenerator/ModelGenerator.h"
#include "../../LagrangeElements/LagrangeElements.h"

/**
 * @brief Test of the class CustomLagrangeElement::ShapeMatrix
 */
int main(int argc, char **argv)
{
    ModelDescriptor::Point p1{0.0, 0.0}, p2{1.0, 0.0}, p3{0.0, 1.0}; /**< simplex in 2D space*/
    ModelDescriptor::Element e{p1, p2, p3};

    CustomLagrangeElement::ShapeMatrix<TLLE::DOF, 3> shapeMatrix{e};

    if (
        shapeMatrix.ShapeFuncValue<0>(p1) == 1.0 &&
        shapeMatrix.ShapeFuncValue<0>(p2) == 0.0 &&
        shapeMatrix.ShapeFuncValue<0>(p3) == 0.0 &&
        shapeMatrix.ShapeFuncValue<1>(p1) == 0.0 &&
        shapeMatrix.ShapeFuncValue<1>(p2) == 1.0 &&
        shapeMatrix.ShapeFuncValue<1>(p3) == 0.0 &&
        shapeMatrix.ShapeFuncValue<2>(p1) == 0.0 &&
        shapeMatrix.ShapeFuncValue<2>(p2) == 0.0 &&
        shapeMatrix.ShapeFuncValue<2>(p3) == 1.0)
    {
    }
    else
    {
        std::cerr << "Fail "
                  << "Wrong values of shape functions at element nodes"
                  << std::flush;
        return -1;
    }

    auto g1 = shapeMatrix.ShapeFuncGradient<0>();
    auto g2 = shapeMatrix.ShapeFuncGradient<1>();
    auto g3 = shapeMatrix.ShapeFuncGradient<2>();
    if (g1.dfdx != -1.0 ||
        g1.dfdy != -1.0 ||
        g2.dfdx != 1.0 ||
        g2.dfdy != 0.0 ||
        g3.dfdx != 0.0 ||
        g3.dfdy != 1.0)
    {
        std::cerr << "Fail "
                  << "Wrong values of shape function gradients"
                  << std::flush;
        return -1;
    }

    std::cout << "Pass ";
    return 0;
}