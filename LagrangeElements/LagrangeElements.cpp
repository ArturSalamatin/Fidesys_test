#include "LagrangeElements.h"

namespace LagrangeElements
{

    double TriangleLinearLagrangeElement::Area() const { return AreaTwice * 0.5; };

    TriangleLinearLagrangeElement::TriangleLinearLagrangeElement(const ModelDescriptor::Element &coords, const ModelDescriptor::MaterialPropDesc &propDesc) noexcept
        : Coords{coords},
          shapeFuncCoefs{
              getShapeFuncCoef(Coords(1), Coords(2), Coords(0)),
              getShapeFuncCoef(Coords(2), Coords(0), Coords(1)),
              getShapeFuncCoef(Coords(0), Coords(1), Coords(2))}
    {
        AreaTwice = (Coords(0).x() * shapeFuncCoefs[0].b +
                     Coords(1).x() * shapeFuncCoefs[1].b +
                     Coords(2).x() * shapeFuncCoefs[2].b);
        for (size_t i = 0; i < 3; ++i)
        {
            shapeFuncCoefs[i].a /= AreaTwice;
            shapeFuncCoefs[i].b /= AreaTwice;
            shapeFuncCoefs[i].c /= AreaTwice;
        }

        setStrainMatrix();
        setStiffnessMatrix(propDesc.E, propDesc.mu);
    }


    void v::setStrainMatrix() noexcept
    {
        B << shapeFuncCoefs[0].a, 0, shapeFuncCoefs[1].a, 0, shapeFuncCoefs[2].a, 0,
            0, shapeFuncCoefs[0].b, 0, shapeFuncCoefs[1].b, 0, shapeFuncCoefs[2].b,
            shapeFuncCoefs[0].b, shapeFuncCoefs[0].a,
            shapeFuncCoefs[1].b, shapeFuncCoefs[1].a,
            shapeFuncCoefs[2].b, shapeFuncCoefs[2].a;
    }

    void TriangleLinearLagrangeElement::setMaterialMatrix(double E, double mu) noexcept
    {
        c << 1, mu, 0, mu, 1, 0, 0, 0, (1 - mu) / 2;
        c *= E / (1 - mu * mu);
    }
    void TriangleLinearLagrangeElement::setStiffnessMatrix(double E, double mu) noexcept
    {
        setMaterialMatrix(E, mu);
        k = Area() * B.transpose() * c * B;
    }

    TriangleLinearLagrangeElement::ShapeFuncCoef TriangleLinearLagrangeElement::getShapeFuncCoef(
        const ModelDescriptor::Point &p1,
        const ModelDescriptor::Point &p2,
        const ModelDescriptor::Point &p3) const noexcept
    {
        return TriangleLinearLagrangeElement::ShapeFuncCoef{p2.x() * p3.y() - p3.x() * p2.y(), p2.y() - p3.y(), p3.x() - p2.x()};
    }

} // LagrangeElements