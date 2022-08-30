#ifndef MODELDESCRIPTOR_H
#define MODELDESCRIPTOR_H

// #include <vector>
#include <map>
#include <unordered_map>

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

    using Point2D = Eigen::Vector2d; /**< (x;y) coordinates of points in 2D space, in meters */
    using Node = struct
    {
        unsigned int id;
        Point2D p;
    }; /**< This struct binds the point (x;y) to its id in the mesh */

    using Points = std::unordered_map<unsigned int, Point2D>; /**< Container for points in 2D space accessed by its id in the mesh */

    struct GridDesc
    {
    public:
        Points points;

        void push(const Node &node)
        {
            points.insert({node.id, node.p});
        }
    };
} // ModelDescriptor
#endif