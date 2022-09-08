#include "ModelGenerator.h"

namespace ModelGenerator
{
    ModelDescriptor::GridDesc
    MeshDescriptorFromFile(const std::string &fileName)
    {
        FileParser::KfileParser parser{fileName};
        parser.parse();

        return {std::move(parser.p), std::move(parser.e)};
    }

    ModelDescriptor::MaterialPropDesc
    MaterialPropDescDefault()
    {
        return ModelDescriptor::MaterialPropDesc{2E11, 0.3};
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
        KfileParser::~KfileParser()
        {
            stream.close();
        }

        void KfileParser::parse()
        {
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
                            throw std::runtime_error("The amount of nodes is insufficient to construct any finite element.");
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
            if (p.empty())
                throw std::runtime_error("NODE section is not found in the file.");
            if (e.empty())
                throw std::runtime_error("ELEMENT_SHELL section is not found in the file.");
        }

        ModelDescriptor::PointWithID
        KfileParser::parse_node(const std::string &s)
        {

            if (s.empty())
                throw std::runtime_error("Current string is empty. It does not contain NODE description.");

            ModelDescriptor::Point p;

            std::stringstream str{s};
            unsigned int id;
            double x, y;

            str >> id;
            str >> x >> y;

            return ModelDescriptor::PointWithID{id, ModelDescriptor::Point{x, y}};
        }

        ModelDescriptor::ElementDescWithID
        KfileParser::parse_element(const std::string &s)
        {
            if (s.empty())
                throw std::runtime_error("Current string is empty. It does not contain ELEMENT description.");

            ModelDescriptor::Point p;

            std::stringstream str{s};
            unsigned int id;
            ModelDescriptor::ElementDesc v;
            unsigned int temp; /**< This column is irrelevant*/

            str >> id >> temp >> v(0) >> v(1) >> v(2);

            return ModelDescriptor::ElementDescWithID{id, std::move(v)}; /**< point IDs are returned in a sorted order*/
        }

        ModelDescriptor::PointContainer
        KfileParser::parse_section_node()
        {
            ModelDescriptor::PointContainer P;
            std::string str;
            std::getline(stream, str); /**<  get a line from istream. For NODE section it contains node headers. Skip them*/
            while (!stream.eof())
            {
                std::getline(stream, str); /**<  get a line from istream*/

                if (str[0] == '$' || str == "*END")
                    return P;

                auto point = parse_node(str);
                P.insert({point.id, point.p});
            }

            if (P.empty())
                throw std::runtime_error("Nodes container is empty.");

            return P;
        }

        ModelDescriptor::ElementsDescContainer
        KfileParser::parse_section_element()
        {
            ModelDescriptor::ElementsDescContainer E;
            std::string str;
            while (!stream.eof())
            {
                std::getline(stream, str); /*<  get a line from istream*/

                if (str[0] == '$' || str == "*END")
                    return E;

                auto elem = parse_element(str);
                E.insert({elem.id, elem.e});
            }
            if (E.empty())
                throw std::runtime_error("Eelements container is empty.");

            return E;
        }

    } // FileParser
} // ModelGenerator