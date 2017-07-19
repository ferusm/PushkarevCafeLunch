#include <iostream>
#include <memory>

#include <tgbot/tgbot.h>

#include "Params.h"
#include "Logger.h"
#include "Parser.h"

#include <windows.h>

int main(const int argc, const char* const argv[]) {
    SetConsoleOutputCP(CP_UTF8);

    std::shared_ptr<Params> paramsPtr = std::make_shared<Params>(argc, argv);
    std::shared_ptr<Logger> loggerPtr = std::make_shared<Logger>(paramsPtr);
    std::shared_ptr<Parser> parserPtr = std::make_shared<Parser>(loggerPtr);

    TgBot::Bot bot("");

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Привет, " + message->from->firstName + "!");
    });

    bot.getEvents().onNonCommandMessage([&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Используйте команды. Список доступных команд можно получить спомощью: /help");
    });

    bot.getEvents().onAnyMessage([&bot ,&loggerPtr](TgBot::Message::Ptr message) {
        loggerPtr->wtite(std::to_string(message->from->id) + " : " + message->from->firstName
                         + " " + message->from->lastName
                         + ((!message->from->username.empty())?(" : " + message->from->username): "") + " - "
                         + message->text
        );
    });

    bot.getEvents().onCommand("help", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Список доступных команд:\n /lunch - меню бизнес-ланча");
    });

    bot.getEvents().onCommand("lunch", [&bot, &parserPtr](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Сейчас можно заточить:\n" + parserPtr->getLunchMenu()
                                                    + "Приятного аппетита!");
    });
    try {
        loggerPtr->wtite("Bot username: " + bot.getApi().getMe()->username + " started.");
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}