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

	//Input �f��, ���
	//Return �f��,�ƾ�
	std::map<int, ItemData> checkItemNumbersInFile(std::set<int> itemNumbers, std::string file);

};