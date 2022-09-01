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

    
    std::ostream& operator<<(std::ostream& o, const Eigen::Vector2d& v)
    {
        o << std::left << std::setw(3) <<  "x:" << std::right << std::scientific << std::setprecision(6) << v(0);
        o << ";\t";
        o << std::left << std::setw(3) <<  "y:" << std::right << std::scientific << std::setprecision(6) << v(1);
        o << std::endl;
        return o;
    }

    
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::Node& node)
    {
        o << "<<<ModelDescriptor::Node>>>\n";
        o << std::left << std::setw(4) <<  "id:" << std::right << node.id;
        o << '\n';
        o << node.p;

        return o;
    }

    
    std::ostream& operator<<(std::ostream& o, const ModelDescriptor::Points& p)
    {
        o << "<<<ModelDescriptor::Points>>>\n";
        o << std::left << std::setw(17) <<  "container size:" << std::right << p.size();
        o << '\n';

        for(const auto& e : p)
            o << ModelDescriptor::Node{e.first, e.second};

        return o;
    }

}