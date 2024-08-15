#include "pch.h"
#include "MyLogger.h"

Logger* Logger::instance = nullptr;
Logger* Logger::getInstance()
{
	if (!instance) {
		instance = new Logger();
	}
	return instance;
}
void Logger::destroyInstance()
{
	if (instance) {
		delete instance;
		instance = nullptr;
		spdlog::drop_all();  // 釋放所有 logger
	}
}

Logger::Logger()
{
	if (!basicFileLogger) {
		auto basicFileLogger = spdlog::basic_logger_mt("basicFileLogger", "logs/logs.txt");
		spdlog::set_default_logger(basicFileLogger);  // 將此 logger 設為默認 logger
		spdlog::set_level(spdlog::level::debug);
		spdlog::flush_on(spdlog::level::debug);  // 每當輸出info級別或更高級別的日誌時自動刷新緩衝區
	}

}
Logger::~Logger()
{
	destroyInstance();
}

