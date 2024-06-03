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
namespace gui {
    class Thystame : public ARock {
        public:
            Thystame(std::uint32_t rockQuantity = 0 ) : ARock( rockQuantity ) {};
    };
}
