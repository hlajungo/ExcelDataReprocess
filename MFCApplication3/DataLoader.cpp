#include "pch.h"
#include "DataLoader.h"


#include <OpenXLSX.hpp>
using namespace OpenXLSX;

#include <windows.h>


DataLoader* DataLoader::instance = nullptr;
DataLoader::DataLoader()
{

}
DataLoader::~DataLoader()
{
	this->destroyInstance();
}
DataLoader* DataLoader::getInstance()
{
	if (!instance) {
		instance = new DataLoader();
	}
	return instance;
}

void DataLoader::destroyInstance()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

std::list<int> DataLoader::loadFiles(std::string directoryPath)
{
	spdlog::info("DataLoader: read dir = " + directoryPath);

	std::list<int> myList;


	std::string searchPath = directoryPath + "\\*.xlsx";
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			//stop for ~$*.xlsx file
			if (std::string(findFileData.cFileName).find("~$") != std::string::npos) {
				spdlog::info("DataLoader:Found~$*.xlsx file = {} ,have file is opened.",findFileData.cFileName);
				break;
			}

			//create full path
			std::string fullPath = directoryPath;
			if (!fullPath.empty() && fullPath.back() != '\\' && fullPath.back() != '/') {
				fullPath += '\\';
			}
			fullPath += findFileData.cFileName;
			spdlog::info("DataLoader:Found.xlsx file = {}",findFileData.cFileName);


			OpenXLSX::XLDocument doc;
			doc.open(fullPath);

			auto sheetCount = doc.workbook().sheetCount();
			spdlog::info("DataLoader: sheetCount  = {}", sheetCount);

			////output all worksheet
			//for (size_t i = 1; i <= sheetCount; ++i) {
			//	auto sheet = doc.workbook().worksheet(i); // 根據索引獲取工作表
			//	spdlog::info("DataLoader: Sheet {}  = {}"  ,i , sheet.name());
			//}

			auto sheet = doc.workbook().worksheet("Sheet1");
			uint32_t lastRow = 2;
			while (sheet.cell("C" + std::to_string(lastRow)).value().typeAsString() != "empty") {
				int cellValue = sheet.cell("C" + std::to_string(lastRow)).value();
				myList.push_back(cellValue);

				//spdlog::info("DataLoader: Cxx Value = {}", cellValue);
				lastRow++;
			}
			lastRow--;  // Adjust since loop goes one step too far
			spdlog::info("DataLoader: Last row = {}", lastRow);



			doc.close();


		} while (FindNextFileA(hFind, &findFileData) != 0);
		FindClose(hFind);
	}

	return myList;
}

std::set<int> DataLoader::extractUniqueItemNumbers(std::list<int> data)
{
	std::set<int> mySet;
	mySet.insert(std::make_move_iterator(data.begin()), std::make_move_iterator(data.end()));
	return mySet;
}
