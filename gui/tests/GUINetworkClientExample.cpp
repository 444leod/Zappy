/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** main
*/

#include "Client.hpp"
#include "macros.h"
#include <iostream>
#include <thread>

int main(UNUSED int argc, UNUSED char const *argv[])
{
    try {
        gui::ntw::Client Client(4242);

        Client.connectToServer(); // blockant, max 5s

        Client.queueRequest("msz");
        Client.sendRequests(std::chrono::milliseconds(1000)); // blockant, max 1s or will throw exception

        while (!Client.receive()); //wait for response

        if (!Client.hasResponses())
            throw gui::ntw::Client::ClientException("Failed to receive response");

        const std::string response = Client.popResponse(); // get last response (First In First Out)
        std::cout << "received response: " << response << std::endl;

        Client.disconnect();

    } catch (const gui::ntw::Client::ClientTimeoutException& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const gui::ntw::Client::ClientNotConnectedException& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const gui::ntw::Client::ClientException& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}

