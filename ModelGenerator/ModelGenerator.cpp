#include "ModelGenerator.h"

namespace ModelGenerator
{

    ModelFactory_FromFile::ModelFactory_FromFile(std::string fileName) noexcept : fileName{fileName}
    {
        FileParser::KfileParser parser{fileName};
    }

    namespace FileParser
    {
        KfileParser::KfileParser(const std::string &fName)
        {
            stream.open(fName);
            if (!stream.is_open())
            {
                throw std::runtime_error("Could not open file " + fName);
            }
        }

        ModelDescriptor::Node
        KfileParser::parse_node(const std::string &s)
        {
            ModelDescriptor::Point2D p;

            std::stringstream str{s};
            unsigned int id;
            double x, y;

            str >> id;
            str >> x >> y;

            return ModelDescriptor::Node{id, ModelDescriptor::Point2D{x, y}};
        }

        ModelDescriptor::Points
        KfileParser::parse_section_node()
        {
            ModelDescriptor::Points P;
            std::string str;
            std::getline(stream, str); /*<  get a line from istream. For NODE section it contains node headers. Skip them*/
            while (true)
            {
                std::getline(stream, str); /*<  get a line from istream*/

                if (str[0] == '$' || str == "*END")
                    return P;

                auto point = parse_node(str);
                P.insert({point.id, point.p});
            }
        }

    } // FileParser

} // ModelGenerator