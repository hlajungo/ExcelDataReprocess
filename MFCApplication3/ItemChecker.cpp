#include "pch.h"
#include "ItemChecker.h"

#include <OpenXLSX.hpp>
using namespace OpenXLSX;


ItemChecker* ItemChecker::instance = nullptr;
ItemChecker::ItemChecker()
{
}
ItemChecker::~ItemChecker()
{
	this->destroyInstance();

}

ItemChecker* ItemChecker::getInstance()
{
	if (!instance) {
		instance = new ItemChecker();
	}
	return instance;
}

void ItemChecker::destroyInstance()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}


std::map<int, ItemData> ItemChecker::checkItemNumbersInFile(std::set<int> itemNumbers, std::string file)
{
	spdlog::info("ItemChecker: read file = " + file);
	ItemData mydata;
	std::map<int, ItemData> mymap;

	OpenXLSX::XLDocument doc;
	doc.open(file);
	auto sheet = doc.workbook().worksheet("Sheet1");

	//search for A
	uint32_t lastRow = 5;
	while (sheet.cell("A" + std::to_string(lastRow)).value().typeAsString() != "empty") {
		int cellValue = sheet.cell("A" + std::to_string(lastRow)).value();
		auto it = itemNumbers.find(cellValue);
		if (it != itemNumbers.end()) {
			mydata.itemNumber = cellValue;
			mydata.SalesQuantity = sheet.cell("A" + std::to_string(lastRow)).offset(0, 2).value();
			mydata.salesAmount = sheet.cell("A" + std::to_string(lastRow)).offset(0, 3).value();
			mymap.insert(std::pair<int, ItemData>(cellValue, mydata));
			spdlog::info("ItemChecker: Find = {}", cellValue);
		}
		else {
			//mydata.itemNumber = -1;
			//mydata.SalesQuantity = -1;
			//mydata.salesAmount = -1;
			//mymap.insert(std::pair<int, ItemData>(cellValue, mydata));
			spdlog::info("ItemChecker: Can't find = {}",cellValue);
		}

		//spdlog::info("DataLoader: Cxx Value = {}", cellValue);
		lastRow++;
	}
	lastRow--;  // Adjust since loop goes one step too far
	spdlog::info("ItemChecker: Last row A = {}", lastRow);

	//search for F
	uint32_t lastRow2 = 5;
	while (sheet.cell("F" + std::to_string(lastRow2)).value().typeAsString() != "empty") {
		int cellValue = sheet.cell("F" + std::to_string(lastRow2)).value();
		auto it = itemNumbers.find(cellValue);
		if (it != itemNumbers.end()) {
			mydata.itemNumber = cellValue;
			mydata.SalesQuantity = sheet.cell("F" + std::to_string(lastRow2)).offset(0, 2).value();
			mydata.salesAmount = sheet.cell("F" + std::to_string(lastRow2)).offset(0, 3).value();
			mymap.insert(std::pair<int, ItemData>(cellValue, mydata));
			spdlog::info("ItemChecker: Find = {}", cellValue);
		}
		else {
			//mydata.itemNumber = -1;
			//mydata.SalesQuantity = -1;
			//mydata.salesAmount = -1;
			//mymap.insert(std::pair<int, ItemData>(cellValue, mydata));
			spdlog::info("ItemChecker: Can't find = {}", cellValue);
		}

		//spdlog::info("DataLoader: Cxx Value = {}", cellValue);
		lastRow2++;
	}
	lastRow2--;  // Adjust since loop goes one step too far

	spdlog::info("ItemChecker: Last row F = {}", lastRow2);

	doc.close();


	return mymap;
}

