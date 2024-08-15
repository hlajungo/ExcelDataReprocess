// pch.cpp: 對應到先行編譯標頭的來源檔案

#include "pch.h"

Logger* basicFileLogger = Logger::getInstance();

// 使用先行編譯的標頭時，需要來源檔案才能使編譯成功。
