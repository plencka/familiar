#pragma once
#include "Filesystem/File.hpp"
#include "Serialization/Interfaces/ISerializable.hpp"

namespace FamiliarEngine {
    class Deserializer : public File<std::ifstream> {
    private:
        ISerializable* serializable;

    public:
        Deserializer(ISerializable* serializableObject) :
            File(serializableObject->getFilename(), serializableObject->getPath()),
            serializable(serializableObject) {
            stream->open(pathName,
                std::ifstream::in
                | std::ifstream::binary);
        };

        void handle() override {
            if (stream->is_open())
            {
                SerializablePackage package;
                while (stream->good())
                {
                    package.getRecordFromStream(*stream);
                }

                serializable->deserialize(package);
            }
        }
    };
}
