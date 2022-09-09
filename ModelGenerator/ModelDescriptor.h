#ifndef MODELDESCRIPTOR_H
#define MODELDESCRIPTOR_H

// #include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <algorithm>

#include "../eigen/Eigen/Dense"

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
        MaterialPropDesc(double E, double mu) noexcept;
        double E;  /**< Young modulus, Pa */
        double mu; /**<  Poisson's ratio, - */
    };

    using Point = Eigen::Vector2d; /**< (x;y) coordinates of points in 2D space, in meters */
    // {
    //     Point() = default;
    //     Point(double x, double y)
    //         : Eigen::Vector2d{x, y}
    //     {
    //     }
    //     double X() { return (*this)(0); }
    //     double Y() { return (*this)(1); }
    // };

    struct PointWithID
    {
        unsigned int id;
        Point p;
    }; /**< This struct binds the point (x;y) to its id in the mesh */

    using ElementDesc = Eigen::Matrix<unsigned int, 3, 1>; /**< global indices of points in 2D space that form the FEM, in meters */

    /**
     * @brief Struct describing a finite element with ID. The nodes f the element are stored in a sorted order.
     *
     */
    struct ElementDescWithID
    {
        ElementDescWithID(unsigned int id, const ElementDesc &e) noexcept;

        unsigned int id; /**< ID of the FEM element*/
        ElementDesc e;   /**< IDs of nodes that form the element*/
    };

    using PointContainer = std::unordered_map<unsigned int, Point>;              /**< Container for points in 2D space accessed by its id in the mesh. The ids are not nesecceraly indexed as 0,1,2,.. */
    using ElementsDescContainer = std::unordered_map<unsigned int, ElementDesc>; /**< Container for FEM elements in 2D space accessed by its id in the element container. The ids are not nesecceraly indexed as 0,1,2,.. */

    using Element = Eigen::Matrix<Point, 3, 1>;                          /**< (x;y) coords of 3 points in 2D space that form the triangular FEM, in meters */
    using ElementsContainer = std::unordered_map<unsigned int, Element>; /**< Container for FEM elements in 2D space accessed by its id in the element container. The ids are not nesecceraly indexed as 0,1,2,.. */

    struct TriangleLagrangeElement
    {
        using ShapeMatrix = Eigen::Matrix<double, 2, 6, Eigen::RowMajor>;
        using StrainMatrix = Eigen::Matrix<double, 3, 6, Eigen::RowMajor>;
        using MaterialMatrix = Eigen::Matrix<double, 3, 3, Eigen::RowMajor>;
        using StiffnessMatrix = Eigen::Matrix<double, 6, 6, Eigen::RowMajor>;
        using ShapeFuncCoef = struct
        {
            double a;
            double b;
            double c;
        };

        double Area();
        TriangleLagrangeElement(const Element &coords, const MaterialPropDesc &propDesc) noexcept;
        Element Coords;
        std::array<ShapeFuncCoef, 3> shapeFuncCoefs;
        double AreaTwice;

        StrainMatrix B;
        MaterialMatrix c;
        StiffnessMatrix k;

        ShapeMatrix getShapeMatrix(double x, double y) const noexcept;

    protected:
        template <unsigned char idx>
        double ShapeFunc(double x, double y) const noexcept
        {
            static_assert(idx < 3, "TriangleLagrangeElement::ShapeFunc wrong template parameter");
            return (shapeFuncCoefs[idx].a +
                    shapeFuncCoefs[idx].b * x +
                    shapeFuncCoefs[idx].c * y);
        }

        void setStrainMatrix() noexcept;

        void setMaterialMatrix(double E, double mu) noexcept;

        void setStiffnessMatrix(double E, double mu) noexcept;

        ShapeFuncCoef getShapeFuncCoef(const Point &p1, const Point &p2, const Point &p3) const noexcept;
    };

    struct GridDesc
    {
    public:
        PointContainer points;
        ElementsDescContainer elementsDesc;

        ElementsContainer elements;
        GridDesc() = default;

        GridDesc(const PointContainer &points, const ElementsDescContainer elements);

        // void push(const Node &node)
        // {
        //     points.insert({node.id, node.p});
        // }

        // void push(const Element &elem)
        // {
        //     elements.insert({elem.id, elem.e});
        // }
    };
} // ModelDescriptor
#endif