/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** main
*/

#include "ZappyClient.hpp"
#include <iostream>
#include <thread>

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;
    try {
        GUI::ZappyClient ZappyClient(4242);

        ZappyClient.connectToServer(); // blockant, max 5s

        ZappyClient.queueRequest("msz");
        ZappyClient.sendRequests(std::chrono::milliseconds(1000)); // blockant, max 1s or will throw exception

        while (!ZappyClient.receive()); //wait for response

        if (!ZappyClient.hasResponses())
            throw GUI::ZappyClient::ZappyClientException("Failed to receive response");

        const std::string response = ZappyClient.popResponse(); // get last response (First In First Out)
        std::cout << "received response: " << response << std::endl;

        ZappyClient.disconnect();

    } catch (const GUI::ZappyClient::ZappyClientException& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}

