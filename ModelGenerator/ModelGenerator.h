#ifndef MODELGENERATOR_H
#define MODELGENERATOR_H

#include <filesystem>
#include <fstream>
#include <string>
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
        ModelFactory_FromFile(std::string fileName) :
            fileName{fileName}
            {
                FileParser::KfileParser parser{};

            }


   
    };

    namespace FileParser
    {
        /**
         * @brief The class parses the test file with the Fidesys spesification
         * 
         */
        class KfileParser
        {

        };

    } // FileParser
} // ModelGenerator

#endif