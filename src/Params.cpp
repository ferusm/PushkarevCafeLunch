//
// Created by FERusM on 19.07.2017.
//

#include "Params.h"

Params::Params(const int argc, const char* const argv[]):logPath("log.txt"), fileLogging(false), consoleLogging(true){
    for(int i = 1; i < argc; ++i)
    {
        std::string arg(argv[i]);
        if((arg == "-logPath"))
        {
            this->logPath = argv[++i];
            this->fileLogging = true;
            continue;
        }
    }
}

void Params::setConsoleLogging(const bool isEnabled) {
    this->consoleLogging = isEnabled;
}

void Params::setFileLogging(const bool isEnabled) {
    this->fileLogging = isEnabled;
}

std::string Params::getLogFilePath() const {
    return this->logPath;
}

bool Params::fileLoggingEnabled() const {
    return this->fileLogging;
}

bool Params::consoleLoggingEnabled() const {
    return this->consoleLogging;
}