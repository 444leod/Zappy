/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Thystame
*/

#pragma once

#include "ARock.hpp"

/**
 * @brief Class representing thystame in the simulation
 * @note Thystame is a resource that can be found on the map
 * @note Herited from ARock class
*/
class Thystame : public gui::ARock {
    public:
        Thystame(std::uint32_t rockQuantity = 0 ) : gui::ARock( rockQuantity ) {};
};
