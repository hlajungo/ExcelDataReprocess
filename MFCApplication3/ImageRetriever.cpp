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
		image.data,             // ��l�Ϲ��ƾ�unsigned char*
		image.width,            // ��l�Ϲ��e��int
		image.height,           // ��l�Ϲ�����int
		0,                      // ��l�Ϲ��B�T�]�p�G�ƾڬO�s�򪺡A�i�H�]��0�^
		resized_data,           // ��X�Ϲ��ƾ�
		new_width,              // ��X�Ϲ��e��
		new_height,             // ��X�Ϲ�����
		0,                      // ��X�Ϲ��B�T�]�p�G�ƾڬO�s�򪺡A�i�H�]��0�^
		STBIR_TYPE_UINT8,       // �Ϲ��ƾ������]UINT8���8��L�Ÿ���ơ^
		image.channels,         // �q�D��
		STBIR_ALPHA_CHANNEL_NONE,// ���walpha�q�D��m�]�p�G�S��alpha�q�D�A�]��STBIR_ALPHA_CHANNEL_NONE�^
		0,                      // �ϥθӰѼƨӿ�ܬO�_���z���׳B�z�]�]��0�H�����^
		STBIR_EDGE_CLAMP,       // ��t�欰
		STBIR_EDGE_CLAMP,       // ��t�欰
		STBIR_FILTER_BOX,       // �Y�p�L�o������
		STBIR_FILTER_BOX,       // ��j�L�o������
		STBIR_COLORSPACE_SRGB,  // ��m�Ŷ�
		nullptr                 // �ۭq�v������СA�p�G���ݭn�h��nullptr
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
	// �O�s PNG ���
	int stride_in_bytes = width * channels; // �C�@�檺�r�`��
	if (stbi_write_png(filename, width, height, channels, data, stride_in_bytes)) {
		spdlog::info("PDFGenerator: PNG file saved successfully:{}", filename);
	}
	else {
		spdlog::info("PDFGenerator: Failed to save PNG file: {}", filename);
	}
}
