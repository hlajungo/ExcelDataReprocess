#pragma once

#include "map"
#include "ItemData.h"

#define HPDF_DLL
#include <hpdf.h>

class PDFGenerator
{
public:
	//Input , ��X���W
	void generatePDF(std::map<int, ItemData> itemData, const char* outputFile);
private:
	void addTextToPage(HPDF_Doc pdf, HPDF_Page& page, const std::string& text, int& currentY, int lineHeight);

};

