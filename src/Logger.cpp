//
// Created by FERusM on 19.07.2017.
//

#include "Logger.h"

Logger::Logger(std::shared_ptr<Params> paramsPtr): paramsPtr(paramsPtr){
    spdlog::set_async_mode(4096);
    this->fileLogger = spdlog::basic_logger_mt("file_logger", paramsPtr->getLogFilePath());
    this->fileLogger->set_pattern("[%D - %T] %v");
    this->consoleLogger = spdlog::stdout_logger_mt("console_logger");
    this->consoleLogger->set_pattern("[%D - %T] %v");
}

Logger::~Logger(){
    if (this->paramsPtr->fileLoggingEnabled()) {
        this->fileLogger->info("The bot was turned off correctly");
    }
    if (this->paramsPtr->consoleLoggingEnabled()) {
        this->consoleLogger->info("The bot was turned off correctly");
    }
}

void Logger::wtite(const std::string &str) const{
    if (this->paramsPtr->fileLoggingEnabled()) {
        this->fileLogger->info(str);
    }
    if (this->paramsPtr->consoleLoggingEnabled()) {
        this->consoleLogger->info(str);
    }
}