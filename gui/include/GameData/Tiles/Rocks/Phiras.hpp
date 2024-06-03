/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Phiras
*/

#pragma once

#include "ARock.hpp"

/**
 * @brief Class representing phiras in the simulation
 * @note Phiras is a resource that can be found on the map
 * @note Herited from ARock class
*/
class Phiras : public gui::ARock {
    public:
        Phiras(std::uint32_t rockQuantity = 0 ) : gui::ARock( rockQuantity ) {};
};
