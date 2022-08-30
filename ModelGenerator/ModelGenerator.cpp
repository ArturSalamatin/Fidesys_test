#include "ModelGenerator.h"

ModelGenerator::ModelFactory_FromFile::ModelFactory_FromFile(std::string fileName) noexcept : fileName{fileName}
{
    FileParser::KfileParser parser{fileName};
}
