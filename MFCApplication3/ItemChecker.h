#pragma once
#include <set>
#include <list>
#include <map>

#include "ItemData.h"

class ItemChecker
{
private:
	ItemChecker();
	ItemChecker(const Logger&) = delete;
	ItemChecker& operator=(const Logger&) = delete;
	static ItemChecker* instance;
	static void destroyInstance();
public:
	static ItemChecker* getInstance();
	~ItemChecker();
	//others
public:

	//Input 貨號, 文件
	//Return 貨號,數據
	std::map<int, ItemData> checkItemNumbersInFile(std::set<int> itemNumbers, std::string file);

};