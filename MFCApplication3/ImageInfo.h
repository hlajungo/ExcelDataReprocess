#include <string>

struct ImageInfo {
    int width;         // 圖片寬度
    int height;        // 圖片高度
    int channels;      // 通道數量 (例如，RGB有3個通道)
    unsigned char* data;  // 圖片的數據指針

    ImageInfo() : width(0), height(0), channels(0), data(nullptr) {}
};