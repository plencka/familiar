#pragma once
#include "Serialization/SerializablePackage.hpp"
#include <string>

namespace FamiliarEngine {
    class ISerializable {
    public:
        virtual void serialize(SerializablePackage& package) = 0;
        virtual void deserialize(SerializablePackage& package) = 0;
        virtual std::string getFilename() = 0;
        virtual std::string getPath() = 0;

    protected:
        ISerializable() {};
    };
}
