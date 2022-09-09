#ifndef LAGRANGEELEMENTS_H
#define LAGRANGEELEMENTS_H

#include <array>
#include "CustomLagrangeElement.h"

namespace TLLE // TriangleLinearLagrangeElement
{
    constexpr unsigned char DOF = 2; /**< Degrees Of Freedom per node*/
    constexpr unsigned char LNC = 3; /**< Local Node Count*/

    using TriangleLinearShapeMatrix = CustomLagrangeElement::ShapeMatrix<DOF, LNC>;
    using ShapeMatrix = CustomLagrangeElement::CustomShapeMatrix<DOF>;

    struct LagrangeElement
    {
        using MaterialMatrix = ModelDescriptor::PlainStressMaterialMatrix;

        /**
         * @brief A strain matrix corresponding to a node of an element
         *
         */
        struct StrainMatrix
        {
            Eigen::Matrix<double, 3, DOF, Eigen::RowMajor> val;
            StrainMatrix(const CustomLagrangeElement::ShapeFuncGrad &grad)
            {
                val << grad.dfdx, 0.0, 0.0, grad.dfdy, grad.dfdy, grad.dfdx;
            }
        };

        using StiffnessMatrix = CustomLagrangeElement::CustomStiffnessMatrix<DOF>;

        LagrangeElement(
            const ModelDescriptor::Element &coords,
            const ModelDescriptor::MaterialPropDesc &propDesc,
            const MaterialMatrix& c) noexcept
            : Coords{coords}, N{coords}
        {
            std::array<StrainMatrix, LNC> B{N.ShapeFuncGradient<0>(), N.ShapeFuncGradient<1>(), N.ShapeFuncGradient<2>()};
            for (size_t i = 0; i < LNC; ++i)
                for (size_t j = 0; j < LNC; ++j)
                    K[i][j] = Area() * Eigen::Transpose(B[i].val) * (c.val) * B[j].val;
        }

        std::array<std::array<StiffnessMatrix, LNC>, LNC> K;

    protected:
        ModelDescriptor::Element Coords;
        TriangleLinearShapeMatrix N;
        double Area() const { return N.Area; };
    };

} // TLLE

#endif // LAGRANGEELEMENTS_H