#include "ModelGenerator.h"

namespace ModelGenerator
{
    ModelDescriptor::GridDesc
    ModelDescriptorFromFile(const std::string &fileName)
    {
        FileParser::KfileParser parser{fileName};

        return {std::move(parser.p), std::move(parser.e)};
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

            /**
             * @brief Loop through file lines to find various sections
             *
             */
            while (!stream.eof())
            {
                std::string str;
                std::getline(stream, str);

                if (str[0] == '*') /*< a section is found*/
                {
                    std::stringstream ss{std::move(str)};
                    if (str == "*NODE")
                    {
                        p = parse_section_node();
                        if (p.size() < 3)
                        {
                            throw std::runtime_error("The amount of nodes is insufficient to construct a finite element.");
                        }
                        continue;
                    }
                    if (str == "*ELEMENT_SHELL")
                    {
                        e = parse_section_element();
                        if (e.size() < 1)
                        {
                            throw std::runtime_error("There is no any finite element in the file.");
                        }
                        continue;
                    }
                }
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

        ModelDescriptor::Element
        KfileParser::parse_element(const std::string &s)
        {
            ModelDescriptor::Point2D p;

            std::stringstream str{s};
            unsigned int id;
            ModelDescriptor::Element2D v;
            unsigned int temp; /**< This column is irrelevant*/

            str >> id >> temp >> v(0) >> v(1) >> v(2);

            return ModelDescriptor::Element{id, std::move(v)}; /**< point IDs are returned in a sorted order*/
        }

        ModelDescriptor::Points
        KfileParser::parse_section_node()
        {
            ModelDescriptor::Points P;
            std::string str;
            std::getline(stream, str); /**<  get a line from istream. For NODE section it contains node headers. Skip them*/
            while (true)
            {
                std::getline(stream, str); /**<  get a line from istream*/

                if (str[0] == '$' || str == "*END")
                    return P;

                auto point = parse_node(str);
                P.insert({point.id, point.p});
            }
        }

        ModelDescriptor::Elements
        KfileParser::parse_section_element()
        {
            ModelDescriptor::Elements E;
            std::string str;
            while (true)
            {
                std::getline(stream, str); /*<  get a line from istream*/

                if (str[0] == '$' || str == "*END")
                    return E;

                auto elem = parse_element(str);
                E.insert({elem.id, elem.e});
            }
        }

    } // FileParser
} // ModelGenerator