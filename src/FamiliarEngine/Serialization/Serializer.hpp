#pragma once
#include "Filesystem/File.hpp"
#include "Serialization/Interfaces/ISerializable.hpp"

namespace FamiliarEngine {
    class Serializer : public File<std::ofstream> {
    private:
        ISerializable* serializable;

    public:
        Serializer(ISerializable* serializableObject) :
            File(serializableObject->getFilename(), serializableObject->getPath()),
            serializable(serializableObject) {
            stream->open(pathName,
                std::ofstream::out
                | std::ofstream::binary);
        };

        void handle() override {
            SerializablePackage package;
            serializable->serialize(package);
            package.saveToStream(*stream);
        }
    };
}
