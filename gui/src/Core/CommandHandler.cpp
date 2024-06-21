/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** CommandHandler
*/

#include "CommandHandler.hpp"

void gui::CommandHandler::handleCommand(std::string& command)
{
    static uint16_t wrongCommands = 0;

    std::istringstream iss(command);
    std::string token;
    iss >> token;

    if (token == "ok" || token == "ko")
        return;
    auto it = _responseHandlers.find(token);
    if (it != _responseHandlers.end()) {
        // std::cout << "[DEBUG] Handling command: " << token << "(" << command << ")" << std::endl;
        it->second->receive(command, _gameData);
    } else {
        if (token == "eht")
            return;
        wrongCommands++;
        std::cerr << "Command not found: " << token << std::endl;
        if (wrongCommands > 15) {
            throw ntw::Client::ClientException("Too many wrong commands received. Exiting...");
        }
    }
}
