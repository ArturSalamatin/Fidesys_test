#ifndef MODELGENERATOR_H
#define MODELGENERATOR_H

#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>
#include <exception>
#include <algorithm>

#include "ModelDescriptor.h"

namespace ModelGenerator
{
    /**
     * @brief Factory generating a model from file
     *
     */
    class ModelFactory_FromFile
    {
    protected:
        std::string fileName; /**< File name for the test file with the model descriptor */

    public:
        /**
         * @brief Construct a new ModelFactory_FromFile object
         *
         * @param fileName File name for the test file with the model descriptor
         */
        ModelFactory_FromFile(std::string fileName) noexcept;
    };

    namespace FileParser
    {
        /**
         * @brief The class parses the test file with the Fidesys spesification
         *
         */
        class KfileParser
        {
        public:
            KfileParser() = default;
            KfileParser(const std::string &fName);

        public:
            /**
             * @brief Parse a single line of node record
             *
             * @param s Input string containing a node record
             * @return ModelDescriptor::Node Struct containing node descriptor (id + coords)
             */
            static ModelDescriptor::Node parse_node(const std::string &s);

            /**
             * @brief Parse a 2D element from the string
             *
             * @param s String with the element id and node ids
             * @return ModelDescriptor::Element
             */
            static ModelDescriptor::Element parse_element(const std::string &s);

            /**
             * @brief Parse a NODE section of k-file
             *
             * @return ModelDescriptor::Points Container with mesh points
             */
            ModelDescriptor::Points parse_section_node();

            /**
             * @brief Parse a ELEMENT_SHELL section of k-file
             *
             * @return ModelDescriptor::Elements Container with elements of the model
             */
            ModelDescriptor::Elements parse_section_element();

        protected:
            std::ifstream stream; /*< Stream connected to a file with mesh description*/
        };

    } // FileParser
} // ModelGenerator

#endif