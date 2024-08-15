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

	//Ū���Ϥ�
	//Input �f��, �Ϥ��ؿ�
	//Output �Ϥ�
	ImageInfo retrieveImage(int itemNumber, std::string imagePath);

	//���Y�Ϥ�
	//Input �Ϥ�
	//Output �Ϥ�
	ImageInfo compressImage(ImageInfo image);

	void saveImageAsPng(const char* filename, int width, int height, int channels, unsigned char* data);


private:
	bool fileExists(const std::string& filePath);


};

