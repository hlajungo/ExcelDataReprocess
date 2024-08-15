#include "pch.h"
#include "ImageRetriever.h"
#include <string>

#include <fstream>

#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize.h>


#define _CRT_SECURE_NO_WARNINGS

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>


ImageRetriever* ImageRetriever::instance = nullptr;

ImageRetriever::ImageRetriever()
{
}

ImageRetriever::~ImageRetriever()
{
	this->destroyInstance();
}
void ImageRetriever::destroyInstance()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}
ImageRetriever* ImageRetriever::getInstance()
{
	if (!instance) {
		instance = new ImageRetriever();
	}
	return instance;
}

bool ImageRetriever::fileExists(const std::string& filePath)
{
	std::ifstream file(filePath);
	return file.good();
}


ImageInfo ImageRetriever::retrieveImage(int itemNumber, std::string imagePath)
{
	ImageInfo myimg;
	myimg.data = nullptr;

	int width, height, channels;
	std::stringstream imageBase;
	imageBase << imagePath << '\\' << itemNumber;

	if (fileExists(imageBase.str() + ".png")) {
		imageBase << ".png";
	}
	else if (fileExists(imageBase.str() + ".jpg")) {
		imageBase << ".jpg";
	}
	else {
		spdlog::error("ImageRetriever: Unsupported Image Type(support png, jpg)");
		return myimg;
	}

	spdlog::info("ImageRetriever: Read img \"{}\"", imageBase.str());

	unsigned char* img = stbi_load(imageBase.str().c_str(), &width, &height, &channels, 0);

	if (img) {
		spdlog::info("ImageRetriever: Read Success, Width = {}, Height = {}, Channels = {}", width, height, channels);
		myimg.channels = channels;
		myimg.data = img;
		myimg.height = height;
		myimg.width = width;
		
		// Free the image memory when done
		// This line will make error.
		// stbi_image_free(img);

		return myimg;
	}
	else {
		spdlog::error("ImageRetriever: Failed to load image.");
		return myimg;
	}

}

ImageInfo ImageRetriever::compressImage(ImageInfo image)
{

	int new_width = 200;
	int new_height = 200;
	unsigned char* resized_data = new unsigned char[new_width * new_height * image.channels];

	stbir_resize(
		image.data,             // 原始圖像數據unsigned char*
		image.width,            // 原始圖像寬度int
		image.height,           // 原始圖像高度int
		0,                      // 原始圖像步幅（如果數據是連續的，可以設為0）
		resized_data,           // 輸出圖像數據
		new_width,              // 輸出圖像寬度
		new_height,             // 輸出圖像高度
		0,                      // 輸出圖像步幅（如果數據是連續的，可以設為0）
		STBIR_TYPE_UINT8,       // 圖像數據類型（UINT8表示8位無符號整數）
		image.channels,         // 通道數
		STBIR_ALPHA_CHANNEL_NONE,// 指定alpha通道位置（如果沒有alpha通道，設為STBIR_ALPHA_CHANNEL_NONE）
		0,                      // 使用該參數來選擇是否有透明度處理（設為0以忽略）
		STBIR_EDGE_CLAMP,       // 邊緣行為
		STBIR_EDGE_CLAMP,       // 邊緣行為
		STBIR_FILTER_BOX,       // 縮小過濾器類型
		STBIR_FILTER_BOX,       // 放大過濾器類型
		STBIR_COLORSPACE_SRGB,  // 色彩空間
		nullptr                 // 自訂權重表指標，如果不需要則為nullptr
	);
	//release oringial data
	//stbi_image_free(image.data);


	ImageInfo newImg;
	newImg.channels = image.channels;
	newImg.data = resized_data;
	newImg.height = new_height;
	newImg.width = new_width;
	spdlog::info("ImageRetriever: compress Image Success");


	return newImg;
}



void ImageRetriever::saveImageAsPng(const char* filename, int width, int height, int channels, unsigned char* data) {
	// 保存 PNG 文件
	int stride_in_bytes = width * channels; // 每一行的字節數
	if (stbi_write_png(filename, width, height, channels, data, stride_in_bytes)) {
		spdlog::info("PDFGenerator: PNG file saved successfully:{}", filename);
	}
	else {
		spdlog::info("PDFGenerator: Failed to save PNG file: {}", filename);
	}
}
