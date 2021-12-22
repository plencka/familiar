#pragma once
#include "FamiliarEngine/Filesystem.hpp"
#include "FamiliarEngine/Common.hpp"
#include <vector>
#include <unordered_map>

namespace FamiliarEngine {

    class SerializableRecord{
        uint32_t recordId = 0;
        unsigned long long pSize = 0;
        char* value;
        bool shouldDeleteValue = false;
    public:
        SerializableRecord(std::string name, unsigned long long size, char* pParam, unsigned int depth = 0) {
            recordId = getIdentity(name, depth);
            pSize = size;
            value = pParam;
        }

        SerializableRecord(std::ifstream& fileStream) {
            fileStream.read((char*)&recordId, sizeof(recordId));
            fileStream.read((char*)&pSize, sizeof(pSize));

            value = new char[pSize];
            shouldDeleteValue = true;
            fileStream.read(value, pSize);
            fileStream.ignore(1);
        }

        ~SerializableRecord() {
            if (shouldDeleteValue) {
                delete[] value;
            }
        }

        friend std::ofstream& operator<<(std::ofstream& fileStream, SerializableRecord* record);

        static uint32_t getIdentity(std::string name, unsigned int depth = 0) {
            std::string indexAsText = std::to_string(depth);
            name.push_back('_');
            name.append(indexAsText);

            return Hash::FNV(name.c_str());
        }

        uint32_t getRecordId() {
            return recordId;
        }

        unsigned long long getSize() {
            return pSize;
        }

        char* getValue() {
            return value;
        }
    };

    std::ofstream& operator<<(std::ofstream& fileStream, SerializableRecord* record) {
        fileStream.write((char*)&record->recordId, sizeof(record->recordId));
        fileStream.write((char*)&record->pSize, sizeof(record->pSize));
        fileStream.write(record->value, record->pSize);
        fileStream << '\n';
        return fileStream;
    }

    class SerializablePackage : std::unordered_map<uint32_t, SerializableRecord*> {
    private:
        SerializableRecord* getRecord(uint32_t recordId) {
            return at(recordId);
        }
       
    public:
        ~SerializablePackage() {
            for (auto& record : *this) {
                delete record.second;
            }
        }

        template <class T>
        void insert(T* pParam, std::string name, unsigned int depth = 0) {
            SerializableRecord* record = new SerializableRecord(name, sizeof(T), (char*)pParam, depth);
            emplace(record->getRecordId(), record);
        }

        void insert(std::string* pParam, std::string name, unsigned int depth = 0) {
            SerializableRecord* record = new SerializableRecord(name, pParam->size(), (char*)&pParam[0], depth);
            emplace(record->getRecordId(), record);
        }

        void getRecordFromStream(std::ifstream& fileStream) {
            SerializableRecord* record = new SerializableRecord(fileStream);
            emplace(record->getRecordId(), record);
        }

        template <class T>
        void retrieve(T* value, std::string name, unsigned int depth = 0) {
            uint32_t id = SerializableRecord::getIdentity(name, depth);
            try {
                *value = *getRecord(id)->getValue();
            }
            catch (std::out_of_range range) {
                std::printf("Could not find property with ID: 0x%X\n", id);
            }
        }
        
        void retrieve(std::string* value, std::string name, unsigned int depth = 0) {
            uint32_t id = SerializableRecord::getIdentity(name, depth);
            try {
                SerializableRecord* record = getRecord(id);
                value->resize(record->getSize());
                value->assign(record->getValue());
            }
            catch (std::out_of_range range) {
                std::printf("Could not find property with ID: 0x%X\n", id);
            }
        }

        void saveToStream(std::ofstream& fileStream) {
            for (auto &record : *this) {
                fileStream << record.second;
            }
        }
    };

    class ISerializable {
    public:
        virtual void serialize(SerializablePackage& package) = 0;
        virtual void deserialize(SerializablePackage& package) = 0;
        virtual std::string getFilename() = 0;
        virtual std::string getPath() = 0;

    protected:
        ISerializable() {};
    };

    class Serializer : public File<std::ofstream> {
    private:
        ISerializable* serializable;
    public:
        Serializer(ISerializable* serializableObject) : 
            File(serializableObject->getFilename(), serializableObject->getPath()),
            serializable(serializableObject){
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
