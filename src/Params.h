//
// Created by FERusM on 19.07.2017.
//

#ifndef DSCOFFETELEGRAMBOT_PARAMS_H
#define DSCOFFETELEGRAMBOT_PARAMS_H

#include <string>

class Params {
public:
    Params(const int argc, const char* const argv[]);

    void setFileLogging(const bool isEnabled);
    void setConsoleLogging(const bool isEnabled);
    bool fileLoggingEnabled() const;
    bool consoleLoggingEnabled() const;

    std::string getLogFilePath() const;
protected:
    std::string logPath;
    bool fileLogging;
    bool consoleLogging;
};


#endif //DSCOFFETELEGRAMBOT_PARAMS_H
