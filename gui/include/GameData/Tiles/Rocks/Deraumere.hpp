/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Deraumere
*/

#pragma once

#include "ARock.hpp"

/**
 * @brief Class representing deraumere in the simulation
 * @note Deraumere is a resource that can be found on the map
 * @note Herited from ARock class
*/
namespace gui {
    class Deraumere : public ARock {
        public:
            Deraumere(std::uint32_t quantity = 0) : ARock(quantity) {};
    };
}
