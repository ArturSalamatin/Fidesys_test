#ifndef MODELGENERATOR_H
#define MODELGENERATOR_H

#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>
#include <exception>

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
            KfileParser(std::string fName)
            {
                std::ifstream f{fName};
                if (f.is_open())
                {
                    throw std::runtime_error("Could not open file " + fName);
                }
            }

        protected:
            ModelDescriptor::Node parse_node(const std::string &s)
            {
                ModelDescriptor::Point2D p;

                std::stringstream str{s};
                unsigned int id;
                double x, y;

                str >> id;
                str >> x >> y;

                return ModelDescriptor::Node{id, ModelDescriptor::Point2D{x, y}};
            }

            void parse_section_node(std::istream &is)
            {
                
            }
        };

    } // FileParser
} // ModelGenerator

#endif