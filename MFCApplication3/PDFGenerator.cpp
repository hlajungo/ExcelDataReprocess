#include "pch.h"
#include "PDFGenerator.h"

#include <stb_image_write.h>


void PDFGenerator::addTextToPage(HPDF_Doc pdf, HPDF_Page& page, const std::string& text, int& currentY, int lineHeight)
{
	if (currentY < lineHeight) {
		// 如果空間不足，創建新頁面
		page = HPDF_AddPage(pdf);
		HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
		currentY = 800; // 重設Y坐標
	}

	//Note: xy是高度的概念 小於0不會自動生成新頁
	HPDF_Page_BeginText(page);
	HPDF_Page_SetFontAndSize(page, HPDF_GetFont(pdf, "Helvetica", NULL), 20);
	HPDF_Page_TextOut(page, 50, currentY, text.c_str());
	HPDF_Page_EndText(page);

	currentY -= lineHeight; // 更新Y坐標
}


void PDFGenerator::generatePDF(std::map<int, ItemData> itemData, const char* outputFile)
{

	HPDF_Doc pdf = HPDF_New(NULL, NULL);
	if (!pdf) {
		spdlog::error("PDFGenerator: Failed to create PDF object");
		return;
	}
	spdlog::info("PDFGenerator: Create PDF object success.");


	HPDF_Page page = HPDF_AddPage(pdf);
	HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

	int currentY = 800;
	int lineHeight = 20;
	int imageHeight = 200;
	for (auto it = itemData.begin(); it != itemData.end(); ++it) {
		//write text
		addTextToPage(pdf, page, " itemNumber: " + std::to_string(it->second.itemNumber)
			+ " salesAmount: " + std::to_string(it->second.salesAmount)
			+ " SalesQuantity: " + std::to_string(it->second.SalesQuantity)
			, currentY, lineHeight);


		if (currentY < imageHeight) {
			// 如果空間不足，創建新頁面
			page = HPDF_AddPage(pdf);
			HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
			currentY = 800; // 重設Y坐標
		}

		//write image
		HPDF_Image image = HPDF_LoadPngImageFromFile(pdf, it->second.imgName.c_str());
		spdlog::info("PDFGenerator: Try to load image: {}", it->second.imgName);
		if (!image) {
			spdlog::error("PDFGenerator: Failed to load image");
			HPDF_Free(pdf);
			return;
		}
		spdlog::info("PDFGenerator: Load image success");
		HPDF_Page_DrawImage(page, image, 50, currentY - 200, 200, 200);
		currentY -= 200;



		//after drawing, remove the file.
		if (remove(it->second.imgName.c_str()) == 0) {
			spdlog::info("PDFGenerator: File deleted successfully");
		}
		else {
			spdlog::error("PDFGenerator: Error deleting file");
		}
	}

	//for (int i = 0; i < 100; ++i) {
	//	addTextToPage(pdf, page, "Hello, PDF! This is line " + std::to_string(i + 1), currentY, lineHeight);
	//}

	HPDF_SaveToFile(pdf, outputFile);
	HPDF_Free(pdf);



	return;
}

