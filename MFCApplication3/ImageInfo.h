#include <string>

struct ImageInfo {
    int width;         // �Ϥ��e��
    int height;        // �Ϥ�����
    int channels;      // �q�D�ƶq (�Ҧp�ARGB��3�ӳq�D)
    unsigned char* data;  // �Ϥ����ƾګ��w

    ImageInfo() : width(0), height(0), channels(0), data(nullptr) {}
};