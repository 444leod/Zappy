/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** main
*/

#include "GameDataManager.hpp"
#include "ArgumentChecking.hpp"
#include <cstring>

int main(int ac, char **av)
{
    try {
        std::shared_ptr<gui::ArgumentChecking> argCheck = std::make_shared<gui::ArgumentChecking>();
        argCheck->checkArgs(ac, av);
        std::uint32_t port = std::atoi(av[2]);
        gui::GameDataManager gameDataManager(port);
        while (1)
            gameDataManager.handleRequests();
    } catch (const std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        return 84;
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
