#pragma once
#include "File.hpp"
#include <FamiliarEngine/Common/Hash.hpp>
#include <vector>
#include <map>

namespace FamiliarEngine {

    class SerializableRecord{
        uint32_t recordId = 0;
        unsigned long long pSize = 0;
        char* value;
        bool shouldDeleteValue = false;

    protected:
        void write(std::ofstream* fileStream) {
            fileStream->write((char*)&recordId, sizeof(recordId));
            fileStream->write((char*)&pSize, sizeof(pSize));
            fileStream->write(value, pSize);
        }

        void read(std::ifstream* fileStream) {
            fileStream->read((char*)&recordId, sizeof(recordId));
            fileStream->read((char*)&pSize, sizeof(pSize));

            value = new char[pSize];
            shouldDeleteValue = true;
            fileStream->read(value, pSize);
        }

    public:
        static uint32_t getIdentity(std::string name, unsigned int depth = 0) {
            std::string indexAsText = std::to_string(depth);
            name.push_back('_');
            name.append(indexAsText);

            return Hash::FNV(name.c_str());
        }

        SerializableRecord(std::string name, unsigned long long size, char* pParam, unsigned int depth = 0) {
            recordId = getIdentity(name, depth);
            pSize = size;
            value = pParam;
        }

        ~SerializableRecord() {
            if (shouldDeleteValue) {
                delete[] value;
            }
        }

        uint32_t getRecordId() {
            return recordId;
        }

        unsigned long long getSize() {
            return pSize;
        }

    };

    class SerializablePackage {
    private:
        std::map<uint32_t, SerializableRecord> records;

        SerializableRecord getRecord(std::string name, unsigned int depth = 0) {
            uint32_t recordId = SerializableRecord::getIdentity(name, depth);
        }
    };

    class ISerializable {
    public:
        virtual SerializablePackage serialize() = 0;
        virtual bool deserialize(SerializablePackage package) = 0;

    protected:
        ISerializable() {};
    };

    class Serializer : File<std::ofstream> {
    private:
        unsigned int paramCount = 0;
        std::ofstream fileStream;
        ISerializable* serializable;
    public:
        Serializer(ISerializable& serializableObject, std::string fileName, std::string filePath = "") : 
            File(&fileStream, fileName, filePath),
            serializable(&serializableObject){
            fileStream = std::ofstream(filePath,
                std::ofstream::in
                | std::ifstream::binary);
        };

        void handle() override {

            //serializable->serialize(0, fileStream);
        }
    };

    class Deserializer : File<std::ifstream> {
    private:
        std::ifstream fileStream;
        ISerializable* serializable;
    public:
        Deserializer(ISerializable& serializableObject, std::string fileName, std::string filePath = "") :
            File(&fileStream, fileName, filePath),
            serializable(&serializableObject) {
            fileStream = std::ifstream(filePath,
                std::ifstream::in
                | std::ifstream::binary);
        };

        void handle() override {
            if (fileStream.is_open())
            {
                //serializable->deserialize(0, fileIn);
            }
        }
    };
}
