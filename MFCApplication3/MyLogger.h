#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

class Logger {
	//Single Instance
private:
	Logger();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	static Logger* instance;
	void destroyInstance();

public:
	static Logger* getInstance();
	~Logger();


	//others
public:
	std::shared_ptr<spdlog::logger> basicFileLogger;
};

