#include "StreamOutput.h"

namespace ModelDescriptor
{
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::MaterialPropDesc& desc)
    {
        o << std::left << std::setw(18) <<  "Young modulus:" << std::right << std::scientific << std::setprecision(6) << desc.E;
        o << '\n';
        o << std::left << std::setw(18) <<  "Poisson ratio:" << std::right << std::scientific << std::setprecision(6) << desc.mu;
        o << std::endl;
        return o;
    } 

    
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::Point& v)
    {
        o << std::left << std::setw(3) <<  "x:" << std::right << std::scientific << std::setprecision(6) << v(0);
        o << ";\t";
        o << std::left << std::setw(3) <<  "y:" << std::right << std::scientific << std::setprecision(6) << v(1);
        o << std::endl;
        return o;
    }
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::PointWithID& node)
    {
        o << "<<<ModelDescriptor::Node>>>\n";
        o << std::left << std::setw(4) <<  "id:" << std::right << node.id;
        o << '\n';
        o << node.p;

        return o;
    }
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::PointContainer& p)
    {
        o << "<<<ModelDescriptor::Points>>>\n";
        o << std::left << std::setw(17) <<  "container size:" << std::right << p.size();
        o << '\n';

        for(const auto& e : p)
            o << ModelDescriptor::PointWithID{e.first, e.second};

        return o;
    }





    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::ElementDesc& v)
    {
        o << std::left << std::setw(9) <<  "node_1:" << std::right << std::fixed << v(0);
        o << ";\t";
        o << std::left << std::setw(9) <<  "nnode_2:" << std::right << std::fixed << v(1);
        o << ";\t";
        o << std::left << std::setw(9) <<  "nnode_3:" << std::right << std::fixed << v(2);
        o << std::endl;
        return o;
    }
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::ElementDescWithID& e)
    {
        o << "<<<ModelDescriptor::Element>>>\n";
        o << std::left << std::setw(4) <<  "id:" << std::right << e.id;
        o << '\n';
        o << e.e;

        return o;
    }
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::ElementsDescContainer& e)
    {
        o << "<<<ModelDescriptor::Elements>>>\n";
        o << std::left << std::setw(17) <<  "container size:" << std::right << e.size();
        o << '\n';

        for(auto& el : e)
            o << ModelDescriptor::ElementDescWithID{el.first, std::move(el.second)};

        return o;
    }
}