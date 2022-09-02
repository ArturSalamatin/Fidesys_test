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

    using Point2D = Eigen::Vector2d; /**< (x;y) coordinates of points in 2D space, in meters */
    using Node = struct
    {
        unsigned int id;
        Point2D p;
    }; /**< This struct binds the point (x;y) to its id in the mesh */

    using Element2D = Eigen::Matrix<unsigned int, 3, 1>; /**< (x;y) coordinates of points in 2D space, in meters */
    
    /**
     * @brief Struct describing a finite element with ID. The nodes f the element are stored in a sorted order.
     * 
     */
    struct Element
    {
        Element(unsigned int id, Element2D&& e) : id{id}, e{e}
        {
            std::sort(this->e.begin(), this->e.end());
        }

        unsigned int id; /**< ID of the FEM element*/
        Element2D e;     /**< IDs of nodes that form the element*/
    };

    using Points = std::unordered_map<unsigned int, Point2D>;     /**< Container for points in 2D space accessed by its id in the mesh. The ids are not nesecceraly indexed as 0,1,2,.. */
    using Elements = std::unordered_map<unsigned int, Element2D>; /**< Container for FEM elements in 2D space accessed by its id in the element container. The ids are not nesecceraly indexed as 0,1,2,.. */

    struct GridDesc
    {
    public:
        Points points;
        Elements elements;

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