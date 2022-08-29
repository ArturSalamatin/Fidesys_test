#include "StreamOutput.h"

std::ostream& ModelDescriptor::operator<<(std::ostream& o, const ModelDescriptor::MaterialPropDesc& desc)
    {
        o << std::left << std::setw(18) <<  "Young modulus:" << std::right << std::scientific << std::setprecision(6) << desc.E;
        o << '\n';
        o << std::left << std::setw(18) <<  "Poisson ratio:" << std::right << std::scientific << std::setprecision(6) << desc.mu;
        o << std::endl;
        return o;
    } 