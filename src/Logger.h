//
// Created by FERusM on 19.07.2017.
//

#ifndef DSCOFFETELEGRAMBOT_LOGGER_H
#define DSCOFFETELEGRAMBOT_LOGGER_H


#include <memory>
#include "Params.h"
#include "spdlog/spdlog.h"

class Logger {
public:
    Logger(std::shared_ptr<Params> paramsPtr);
    void wtite(const std::string &str) const;
    ~Logger();

protected:
    std::shared_ptr<Params> paramsPtr;
    std::shared_ptr<spdlog::logger> fileLogger;
    std::shared_ptr<spdlog::logger> consoleLogger;
};


#endif //DSCOFFETELEGRAMBOT_LOGGER_H
