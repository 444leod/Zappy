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
class Deraumere : public gui::ARock {
    public:
        Deraumere(std::uint32_t rockQuantity = 0) : gui::ARock(rockQuantity) {};
};
