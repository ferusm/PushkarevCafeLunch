//
// Created by FERusM on 19.07.2017.
//

#ifndef DSCOFFETELEGRAMBOT_PARSER_H
#define DSCOFFETELEGRAMBOT_PARSER_H

#include <curl/curl.h>

#include <map>
#include <string>
#include <list>

#include "Logger.h"

#include "gumbo/Document.h"
#include "gumbo/Node.h"

#include <boost/thread.hpp>

class Parser {
public:
    Parser(std::shared_ptr<Logger> &loggerPtr);
    std::string getLunchMenu();
    void updateLunchMenu();
protected:
    std::shared_ptr<Logger> loggerPtr;
    std::string lunchMenu;

    boost::shared_mutex lunchMenuMutex;
private:
    std::string getResponse(std::string &&url);
};

#endif //DSCOFFETELEGRAMBOT_PARSER_H
