#pragma once
#include <iostream>
#include <fstream>

class ISerializable {
public:
    virtual bool serialize(std::ostream& stream) = 0;
    virtual bool deserialize(std::istream& is) = 0;

protected:
    ISerializable() {};
};

class FileSerializer {
public:
    static bool write(ISerializable* serializable, const std::string filename) {
        bool success = false;

        std::ofstream fileOut(filename.c_str());

        fileOut.open(filename.c_str(),
            std::ofstream::binary
            | std::ofstream::out);

        fileOut.clear();
        
        success = serializable->serialize(fileOut);

        fileOut.close();

        return success;
    }

    static bool read(ISerializable* serializable, const std::string filename) {
        bool success = false;

        std::ifstream fileIn(filename.c_str(),
            std::ifstream::in
            | std::ifstream::binary);

        if (fileIn.is_open())
        {
            success = serializable->deserialize(fileIn);
        }

        fileIn.clear();
        fileIn.close();

        return success;
    }
};
