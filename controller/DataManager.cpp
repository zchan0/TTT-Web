#include <fstream>
#include <iostream>

#include "DataManager.h"

DataManager& DataManager::getInstance()
{
	static DataManager instance;
	return instance;
}

DataManager::DataManager()
{}

DataManager::~DataManager()
{}

void DataManager::read(const std::string &filename, std::string &out)
{
	std::ifstream file;
	file.open(filename.c_str());
	
	if (!file) {
		std::cerr << "ERROR: cannot open file " << filename << std::endl;
		return;
	}

	std::string line;
	bool first = true;
	out += "[";
	while(!file.eof()) {
		getline(file, line);
		if (!line.empty()) {
			if (!first)
				out += ", ";
			out += line;
			first = false;
		}
	}	
	out += "]";
}

void DataManager::write(const std::string &filename, const std::string &str)
{
	std::ofstream file;
	file.open(filename.c_str(), std::fstream::app);
	file << str << "\n";
	file.close();
}

