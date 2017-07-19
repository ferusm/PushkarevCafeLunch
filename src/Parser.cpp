//
// Created by FERusM on 19.07.2017.
//

#include <iostream>
#include "Parser.h"

void thread_function(Parser *parser_ptr){
    while(true) {
        parser_ptr->updateLunchMenu();
        boost::this_thread::sleep_for(boost::chrono::seconds(600));
    }
}

int writer(char *data, size_t size, size_t nmemb, std::string *buffer)
{
    int result = 0;
    if (buffer != NULL)
    {
        buffer->append(data, size * nmemb);
        result = (int) (size * nmemb);
    }
    return result;
}

Parser::Parser(std::shared_ptr<Logger> &logger_ptr) :loggerPtr(logger_ptr){
    boost::thread parserThread(thread_function, this);
    parserThread.detach();
    loggerPtr->wtite("Parser thread started");
}

std::string Parser::getLunchMenu(){
    boost::shared_lock<boost::shared_mutex>shared_lock(lunchMenuMutex);
    return this->lunchMenu;
}

void Parser::updateLunchMenu() {
    std::string html = getResponse("http://www.cafe-pushkarev.com/biznes-lanch");
    CDocument doc;
    doc.parse(html.c_str());
    CSelection lunch = doc.find(".view-business-lunch-today");
    boost::unique_lock<boost::shared_mutex>unique_lock(lunchMenuMutex);
    lunchMenu.clear();
    if(lunch.nodeNum() != 0){
        CSelection lunch_list = lunch.find("li");
        for (unsigned int i = 0; i < lunch_list.nodeNum(); ++i) {
            lunchMenu += lunch_list.nodeAt(i).text() + "\n";
        }
        loggerPtr->wtite("Lunch menu updated."); // some link
    } else {
        loggerPtr->wtite("Can't update lunch menu. Reason: Can't find lunch menu element.");
    }
    unique_lock.unlock();
}

std::string Parser::getResponse(std::string &&url){
    std::string buffer;

    CURL *curl;
    CURLcode result;
    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        result = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        if (result != CURLE_OK)
            loggerPtr->wtite("error: " + std::to_string(result) + " " + curl_easy_strerror(result));
    } else {
        loggerPtr->wtite("ERROR: could not initalize curl.");
    }
    loggerPtr->wtite("CUrl accepts response from server");
    return buffer;
}
