#pragma once

#include <vector>
#include <list>
#include <set>
#include <string>



class DataLoader
{
	//Single Instance
private:
	DataLoader();
	DataLoader(const Logger&) = delete;
	DataLoader& operator=(const Logger&) = delete;
	static DataLoader* instance;
	static void destroyInstance();
public:
	static DataLoader* getInstance();
	~DataLoader();
	//others
public:

	std::list<int> loadFiles(std::string directoryPath);
	std::set<int> extractUniqueItemNumbers(std::list<int> data);
};

