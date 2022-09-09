#ifndef MODELDESCRIPTOR_H
#define MODELDESCRIPTOR_H

// #include <vector>
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

    /**
     * @brief Material matrix for a plain stress problem
     *
     */
    struct PlainStressMaterialMatrix
    {
        Eigen::Matrix<double, 3, 3, Eigen::RowMajor> val;
        PlainStressMaterialMatrix(const MaterialPropDesc &desc)
        {
            val << 1.0, desc.mu, 0.0, desc.mu, 1.0, 0.0, 0.0, 0.0, (1 - desc.mu) / 2;
            val *= desc.E / (1 - desc.mu * desc.mu);
        }
    };

    using Point = Eigen::Vector2d; /**< (x;y) coordinates of points in 2D space, in meters */

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

    using PointWithIdContainer = std::vector<PointWithID>;
    using ElementsDescWithIdContainer = std::vector<ElementDescWithID>;
    using PointContainer = std::vector<Point>;              /**< Container for points in 2D space accessed by its id in the mesh. The ids are not nesecceraly indexed as 0,1,2,.. */
    using ElementsDescContainer = std::vector<ElementDesc>; /**< Container for FEM elements in 2D space accessed by its id in the element container. The ids are not nesecceraly indexed as 0,1,2,.. */

    using Element = Eigen::Matrix<Point, 3, 1>;                          /**< (x;y) coords of 3 points in 2D space that form the triangular FEM, in meters */
    using ElementsContainer = std::vector<Element>; /**< Container for FEM elements in 2D space accessed by its id in the element container. The ids are not nesecceraly indexed as 0,1,2,.. */

    struct GridDesc
    {
    public:
        std::vector<unsigned int> pointCodes; /**< from [0,1,2..] ids get the original ids*/
        std::unordered_map<unsigned int, unsigned int> reversePointCodes; /**< from original ids restore new ids [0,1,2...]*/

        PointContainer points;
     //   ElementsDescContainer elementsDesc;

        ElementsContainer elements;
        GridDesc() = default;

        GridDesc(const PointWithIdContainer &points, const ElementsDescWithIdContainer elements) noexcept;
        size_t PointsCount() const noexcept { return points.size(); }
        size_t ElementsCount() const noexcept { return elements.size(); }
    };
} // ModelDescriptor
#endif