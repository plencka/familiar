#pragma once
#include "FamiliarEngine/Common.hpp"
#include "FamiliarEngine/Filesystem.hpp"
#include <string>

namespace FamiliarEngine {
    class SerializableRecord {
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

        void toStream(std::ofstream& fileStream) {
            fileStream.write((char*)&recordId, sizeof(recordId));
            fileStream.write((char*)&pSize, sizeof(pSize));
            fileStream.write(value, pSize);
            fileStream << '\n';
        }
    };
}
