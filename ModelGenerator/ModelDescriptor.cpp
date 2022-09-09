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
        //    std::sort(this->e.begin(), this->e.end()); // this operation might ruin the direction of nodes
    }

    GridDesc::GridDesc(const PointContainer &points, const ElementsDescContainer elements)
        : points{points}, elementsDesc{elements}
    {
    }

    double TriangleLagrangeElement::Area() { return AreaTwice * 0.5; };
    TriangleLagrangeElement::TriangleLagrangeElement(const Element &coords, const MaterialPropDesc &propDesc) noexcept
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

    TriangleLagrangeElement::ShapeMatrix TriangleLagrangeElement::getShapeMatrix(double x, double y) const noexcept
    {
        double n1 = ShapeFunc<0>(x, y);
        double n2 = ShapeFunc<1>(x, y);
        double n3 = ShapeFunc<2>(x, y);

        TriangleLagrangeElement::ShapeMatrix out;
        out << n1, 0, n2, 0, n3, 0, 0, n1, 0, n2, 0, n3;
        return out;

        //   return ShapeMatrix{n1, 0, n2, 0, n3, 0, 0, n1, 0, n2, 0, n3};
    }

    void TriangleLagrangeElement::setStrainMatrix() noexcept
    {
        // B = StrainMatrix{
        //     shapeFuncCoefs[0].a, 0, shapeFuncCoefs[1].a, 0, shapeFuncCoefs[2].a, 0,
        //     0, shapeFuncCoefs[0].b, 0, shapeFuncCoefs[1].b, 0, shapeFuncCoefs[2].b,
        //     shapeFuncCoefs[0].b, shapeFuncCoefs[0].a,
        //     shapeFuncCoefs[1].b, shapeFuncCoefs[1].a,
        //     shapeFuncCoefs[2].b, shapeFuncCoefs[2].a};

        B << shapeFuncCoefs[0].a, 0, shapeFuncCoefs[1].a, 0, shapeFuncCoefs[2].a, 0,
            0, shapeFuncCoefs[0].b, 0, shapeFuncCoefs[1].b, 0, shapeFuncCoefs[2].b,
            shapeFuncCoefs[0].b, shapeFuncCoefs[0].a,
            shapeFuncCoefs[1].b, shapeFuncCoefs[1].a,
            shapeFuncCoefs[2].b, shapeFuncCoefs[2].a;
    }

    void TriangleLagrangeElement::setMaterialMatrix(double E, double mu) noexcept
    {
        //  c = E / (1 - mu * mu) * TriangleLagrangeElement::MaterialMatrix{1, mu, 0, mu, 1, 0, 0, 0, (1 - mu) / 2};

        c << 1, mu, 0, mu, 1, 0, 0, 0, (1 - mu) / 2;
        c *= E / (1 - mu * mu);
    }
    void TriangleLagrangeElement::setStiffnessMatrix(double E, double mu) noexcept
    {
        setMaterialMatrix(E, mu);
        k = Area() * B.transpose() * c * B;
    }

    TriangleLagrangeElement::ShapeFuncCoef TriangleLagrangeElement::getShapeFuncCoef(const Point &p1, const Point &p2, const Point &p3) const noexcept
    {
        return TriangleLagrangeElement::ShapeFuncCoef{p2.x() * p3.y() - p3.x() * p2.y(), p2.y() - p3.y(), p3.x() - p2.x()};
    }

} // ModelDescriptor