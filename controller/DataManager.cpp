#include <fstream>
#include <vector>
#include <string>
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

// use by getAllSavedPlayers & getGameBoard, out is array json string
void DataManager::read(const std::string &filename, std::string &out)
{
	read(filename, out, false);
}

// if lastline = true, means only read the last line, for create player
// when create new player need to create another if existed
void DataManager::read(const std::string &filename, std::string &out, bool lastline)
{
	std::ifstream file;
	file.open(filename.c_str());
	
	if (!file) {
		std::cerr << "ERROR: cannot open file " << filename << std::endl;
		return;
	}

	std::string line;
	std::vector<std::string> v;
	while(!file.eof()) {
		getline(file, line);
		if (!line.empty()) 
			v.push_back(line);
	}

	if (v.size() == 0) {
		out = lastline ? "" : "[]";
		file.close();
		return;
	}

	std::vector<std::string>::iterator ptr = v.end() - 1;

	if (lastline) {
		out += (*ptr);
	} else {
		out += "[";
		switch(v.size()) {
			case 1:
				out += v[0]; 
				break;
			default:
				out += (*ptr);
				out += ", ";
				--ptr;
				out += (*ptr);
				break;
		}
		
		out += "]";
	}

	file.close();
}

void DataManager::write(const std::string &filename, const std::string &str)
{
	std::ofstream file;
	file.open(filename.c_str(), std::fstream::app);
	file << str << "\n";
	file.close();
}

void DataManager::empty(const std::string &filename)
{
	std::ofstream file;
	file.open(filename.c_str(), std::ofstream::out | std::ofstream::trunc);
	file.close();
}