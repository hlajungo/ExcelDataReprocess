#pragma once


#include "ImageInfo.h"

class ImageRetriever
{
	//Single Instance
private:
	ImageRetriever();
	ImageRetriever(const Logger&) = delete;
	ImageRetriever& operator=(const Logger&) = delete;
	static ImageRetriever* instance;
	static void destroyInstance();
public:
	static ImageRetriever* getInstance();
	~ImageRetriever();
	//others
public:

	//讀取圖片
	//Input 貨號, 圖片目錄
	//Output 圖片
	ImageInfo retrieveImage(int itemNumber, std::string imagePath);

	//壓縮圖片
	//Input 圖片
	//Output 圖片
	ImageInfo compressImage(ImageInfo image);

	void saveImageAsPng(const char* filename, int width, int height, int channels, unsigned char* data);


private:
	bool fileExists(const std::string& filePath);


};

