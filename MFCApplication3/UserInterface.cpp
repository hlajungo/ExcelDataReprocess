#include "pch.h"
#include "GlobalVariable.h"

#include "UserInterface.h"

#include <fstream>

#include <nlohmann/json.hpp>
using nlohmann::json;

#include "PDFGenerator.h"

#include <sstream>


void UserInterface::StartProcess()
{

	//CString to string
	std::string dataFile = CT2A(m_dataFile);
	std::string imgDir = CT2A(m_imgDir);
	std::string searchDir = CT2A(m_searchDir);

	//saving current to json file, so that next time can show something in edit boxes
	json jsonObj;
	jsonObj["dataFile"] = dataFile;
	jsonObj["imgDir"] = imgDir;
	jsonObj["searchDir"] = searchDir;

	std::ofstream outFile("data.json");
	outFile << jsonObj.dump(4); //縮進 4 個空格的格式
	outFile.close();

	std::list<int> myList;
	std::set<int> myset;
	myList = dataLoader->loadFiles(searchDir);
	myset = dataLoader->extractUniqueItemNumbers(myList);

	////output myList
	//for (const auto& value : myList) {
	//	spdlog::info("UserInterface: myList = {}", value);
	//}

	////output myset
	//for (const auto& value : myset) {
	//	spdlog::info("UserInterface: myset = {}", value);
	//}

	std::map<int, ItemData> mymap;
	mymap = itemChecker->checkItemNumbersInFile(myset, dataFile);

	for (auto it = mymap.begin(); it != mymap.end(); ++it) {
		ImageInfo myimg = imageRetriever->retrieveImage(it->first, imgDir);
		if (myimg.data != nullptr) {
			//Img success
			myimg = imageRetriever->compressImage(myimg);

			std::stringstream ss;
			ss << ".\\tmp\\" << it->second.itemNumber <<".png";

			spdlog::info("UserInterface: filename = {}", ss.str().c_str());
			imageRetriever->saveImageAsPng(ss.str().c_str(), myimg.width, myimg.height, myimg.channels, myimg.data);

			//set img
			it->second.imgName = ss.str().c_str();
			spdlog::info("UserInterface: it->second.imgName = {}", it->second.imgName);

		}
		else {
			spdlog::error("UserInterface: Failed to load image ,key = {}", it->first);
		}
	}

	PDFGenerator myPDFGenerator;
	myPDFGenerator.generatePDF(mymap, "outputFile.pdf");
	////output myset
	//for (const auto& value : myset) {
	//	spdlog::info("UserInterface: myset = {}", value);
	//}


	//AfxMessageBox(this->m_dataFile + '\n' + this->m_imgDir + '\n' + this->m_searchDir);

}
