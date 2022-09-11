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
    double w = 0.1, h = 0.1;
    double tol = 1E-14;

    auto gridDesc{ModelGenerator::GridGenerator(w, h)};
    const auto &p1 = gridDesc.points[0];
    const auto &p2 = gridDesc.points[1];
    const auto &p3 = gridDesc.points[2];

    CustomLagrangeElement::ShapeMatrix<TLLE::DOF, 3> shapeMatrix{gridDesc.elements[0]};

    if (
        std::abs(shapeMatrix.ShapeFuncValue<0>(p1) - 1.0) < tol &&
        std::abs(shapeMatrix.ShapeFuncValue<0>(p2)) < tol &&
        std::abs(shapeMatrix.ShapeFuncValue<0>(p3)) < tol &&
        std::abs(shapeMatrix.ShapeFuncValue<1>(p1)) < tol &&
        std::abs(shapeMatrix.ShapeFuncValue<1>(p2) - 1.0) < tol &&
        std::abs(shapeMatrix.ShapeFuncValue<1>(p3)) < tol &&
        std::abs(shapeMatrix.ShapeFuncValue<2>(p1)) < tol &&
        std::abs(shapeMatrix.ShapeFuncValue<2>(p2)) < tol &&
        std::abs(shapeMatrix.ShapeFuncValue<2>(p3) - 1.0) < tol)
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
    if (std::abs(g1.dfdx + 1.0 / w) > tol ||
        std::abs(g1.dfdy + 1.0 / h) > tol ||
        std::abs(g2.dfdx - 1.0 / w) > tol ||
        std::abs(g2.dfdy) > tol ||
        std::abs(g3.dfdx) > tol ||
        std::abs(g3.dfdy - 1.0 / h) > tol)
    {
        std::cerr << "Fail "
                  << "Wrong values of shape function gradients"
                  << std::endl;
        return -1;
    }

    if (std::abs(shapeMatrix.Area - 0.5 * w * h) > tol)
    {
        std::cerr << "Fail "
                  << "Wrong triangle area: " << shapeMatrix.Area
                  << std::endl;
        return -1;
    }

    std::cout << "Pass ";
    return 0;
}