/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Linemate
*/

#pragma once

#include "ARock.hpp"

/**
 * @brief Class representing linemate in the simulation
 * @note Linemate is a resource that can be found on the map
 * @note Herited from ARock class
*/
namespace gui {
    class Linemate : public ARock {
        public:
            Linemate(std::uint32_t rockQuantity = 0) : ARock(rockQuantity) {};
    };
}
