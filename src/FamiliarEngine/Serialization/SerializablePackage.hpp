#pragma once
#include "Serialization/SerializableRecord.hpp"
#include <unordered_map>

namespace FamiliarEngine {
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
            SerializableRecord* record = 
                new SerializableRecord(name, sizeof(T), (char*)pParam, depth);

            emplace(record->getRecordId(), record);
        }

        void insert(std::string* pParam, std::string name, unsigned int depth = 0) {
            SerializableRecord* record = 
                new SerializableRecord(name, pParam->size(), (char*)&pParam[0], depth);

            emplace(record->getRecordId(), record);
        }

        void getRecordFromStream(std::ifstream& fileStream) {
            SerializableRecord* record = 
                new SerializableRecord(fileStream);

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
            for (auto& record : *this) {
                record.second->toStream(fileStream);
            }
        }
    };
}
