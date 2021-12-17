#pragma once
#include <iostream>
#include <fstream>
#include <type_traits>

template<class FileStream>
class File {
	static_assert(std::is_base_of<std::ios, FileStream>::value, "File's FileStream must inherit from std::ios");

protected:
	FileStream* stream;
	
	const std::string name;
	const std::string path;
	const std::string pathName;

protected:
	File(FileStream* fileStream, std::string filename, std::string filepath = "") :
		stream(fileStream),
		pathName(filepath + filename),
		name(filename),
		path(filepath){}

	~File() {
		if (stream) {
			stream->clear();
			stream->close();
		}
	};

	virtual void handle() = 0;

public:
	std::string getName() {
		return name;
	}

	std::string getPath() {
		return path;
	}

	std::string getPathName() {
		return pathName;
	}
};
