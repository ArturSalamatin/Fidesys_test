#ifndef CUSTOMLAGRANGELEMENT_H
#define CUSTOMLAGRANGELEMENT_H

#include "../eigen/Eigen/SparseCore"
#include "../ModelGenerator/ModelDescriptor.h"

namespace CustomLagrangeElement
{
    template <unsigned char dof>
    using CustomShapeMatrix = Eigen::Matrix<double, dof, dof, Eigen::RowMajor>;

    template <unsigned char dof>
    using CustomStiffnessMatrix = Eigen::Matrix<double, dof, dof, Eigen::RowMajor>;

    using ShapeFuncGrad = struct
    {
        double dfdx;
        double dfdy;
    };

    /**
     * @brief Coefficients describing the Shape Function N (polynomials).
     * For linear elements the number of coefficients is equal to the number of nodes in the element
     * For triangular element it is N = 1 + a*x + b*y
     *
     */
    template <unsigned char lnc>
    using ShapeFuncDesc = std::array<double, lnc>;

    template <unsigned char dof, unsigned char lnc>
    struct ShapeMatrix
    {
        ShapeMatrix(const ModelDescriptor::Element &Coords) noexcept
            : shapeFuncCoefs{
                  getShapeFuncCoef(Coords(0), Coords(1), Coords(2)),
                  getShapeFuncCoef(Coords(1), Coords(2), Coords(0)),
                  getShapeFuncCoef(Coords(2), Coords(0), Coords(1))},
              Area{setArea(Coords)}
        {
            for (size_t i = 0; i < lnc; ++i)
                for (size_t j = 0; j < lnc; ++j)
                {
                    shapeFuncCoefs[i][j] /= 2 * Area;
                }
        }

        /**
         * @brief N = 1 + a*x + b*y
         *
         * @tparam local_node_idx number of nodes of the Finite Element
         * @param x x-ccordinate
         * @param y y-coordinate
         * @return double Calculated shape function value at (x;y)
         */
        template <unsigned char local_node_idx>
        double ShapeFuncValue(double x, double y) const noexcept
        {
            static_assert(local_node_idx < lnc, "CustomLagrangeElement::ShapeMatrix::ShapeFuncValue wrong template parameter");
            return {shapeFuncCoefs[local_node_idx][0] * 1.0 +
                    shapeFuncCoefs[local_node_idx][1] * x +
                    shapeFuncCoefs[local_node_idx][2] * y};
        }
        template <unsigned char local_node_idx>
        double ShapeFuncValue(const ModelDescriptor::Point &p) const noexcept
        {
            return ShapeFuncValue<local_node_idx>(p.x(), p.y());
        }

        template <unsigned char local_node_idx>
        ShapeFuncGrad ShapeFuncGradient(double x = 0.0, double y = 0.0) const noexcept
        {
            static_assert(local_node_idx < lnc, "CustomLagrangeElement::ShapeMatrix::ShapeFuncGradient wrong template parameter");
            return {shapeFuncCoefs[local_node_idx][1],
                    shapeFuncCoefs[local_node_idx][2]};
        }

    protected:
        std::array<ShapeFuncDesc<lnc>, lnc> shapeFuncCoefs;

        ShapeFuncDesc<lnc> getShapeFuncCoef(const ModelDescriptor::Point &p1, const ModelDescriptor::Point &p2, const ModelDescriptor::Point &p3) const noexcept
        {
            return ShapeFuncDesc<lnc>{p2.x() * p3.y() - p3.x() * p2.y(), p2.y() - p3.y(), p3.x() - p2.x()};
        }

        double setArea(const ModelDescriptor::Element &Coords) const
        {
            Eigen::Matrix<double, 3, 3, Eigen::RowMajor> det;
            det << Coords(0).x(), Coords(0).y(), 0.5,
                Coords(1).x(), Coords(1).y(), 0.5,
                Coords(2).x(), Coords(2).y(), 0.5;
            return det.determinant();
        }

    public:
        double Area;
    };

} // CustomLagrangeElement

#endif // CUSTOMLAGRANGELEMENT_H