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
		spdlog::drop_all();  // ����Ҧ� logger
	}
}

Logger::Logger()
{
	if (!basicFileLogger) {
		auto basicFileLogger = spdlog::basic_logger_mt("basicFileLogger", "logs/logs.txt");
		spdlog::set_default_logger(basicFileLogger);  // �N�� logger �]���q�{ logger
		spdlog::set_level(spdlog::level::debug);
		spdlog::flush_on(spdlog::level::debug);  // �C���Xinfo�ŧO�Χ󰪯ŧO����x�ɦ۰ʨ�s�w�İ�
	}

}
Logger::~Logger()
{
	destroyInstance();
}

