/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Sibur
*/

#pragma once

#include "ARock.hpp"

/**
 * @brief Class representing sibur in the simulation
 * @note Sibur is a resource that can be found on the map
 * @note Herited from ARock class
*/
class Sibur : public gui::ARock {
    public:
        Sibur(std::uint32_t rockQuantity = 0) : gui::ARock(rockQuantity) {};
};
