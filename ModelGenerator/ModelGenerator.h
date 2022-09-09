#ifndef MODELGENERATOR_H
#define MODELGENERATOR_H

#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>
#include <exception>

#include "ModelDescriptor.h"

namespace ModelGenerator
{
    /**
     * @brief Factory method generating a model from file
     *
     */
    ModelDescriptor::GridDesc
    MeshDescriptorFromFile(const std::string &fileName);

    /**
     * @brief Generates default material properties
     *
     * @return ModelDescriptor::MaterialPropDesc Decriptor of material properties, Young's modulus and Poisson ratio
     */
    ModelDescriptor::MaterialPropDesc
    MaterialPropDescDefault();

    /**
     * @brief Generates a container of points with corresponding element descriptor container
     *
     * @return std::tuple<ModelDescriptor::PointContainer, ModelDescriptor::ElementsDescContainer>
     */
    std::tuple<ModelDescriptor::PointContainer, ModelDescriptor::ElementsDescContainer>
    SimplexGenerator();

    ModelDescriptor::GridDesc
    GridGenerator();

    namespace FileParser
    {
        /**
         * @brief The class parses the test file with the Fidesys spesification
         *
         */
        class KfileParser
        {
        public:
            /**
             * @brief Construct a new Kfile Parser object cheicking that the file to read from exists
             *
             * @param fName The name of file with NODE and ELEMENT description
             */
            KfileParser(const std::string &fName);
            virtual ~KfileParser();

            /**
             * @brief Parse the entire file with sections to populate e and p fields
             *
             */
            void KfileParser::parse();

            /**
             * @brief Container with mesh elements
             *
             */
            ModelDescriptor::ElementsDescWithIdContainer e;
            /**
             * @brief Container with mesh nodes
             *
             */
            ModelDescriptor::PointWithIdContainer p;

        public: // should be protected/private
            /**
             * @brief Parse a single line of node record
             *
             * @param s Input string containing a node record
             * @return ModelDescriptor::Node Struct containing node descriptor (id + coords)
             */
            static ModelDescriptor::PointWithID parse_node(const std::string &s);

            /**
             * @brief Parse a 2D element from the string
             *
             * @param s String with the element id and node ids
             * @return ModelDescriptor::Element
             */
            static ModelDescriptor::ElementDescWithID parse_element(const std::string &s);

            /**
             * @brief Parse a NODE section of k-file
             *
             * @return ModelDescriptor::Points Container with mesh points
             */
            ModelDescriptor::PointWithIdContainer parse_section_node();

            /**
             * @brief Parse a ELEMENT_SHELL section of k-file
             *
             * @return ModelDescriptor::Elements Container with elements of the model
             */
            ModelDescriptor::ElementsDescWithIdContainer parse_section_element();

        protected:
            std::ifstream stream; /*< Stream connected to a file with mesh description*/
        };

    } // FileParser
} // ModelGenerator

#endif