/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Mendiane
*/

#pragma once

#include "ARock.hpp"

/**
 * @brief Class representing mendiane in the simulation
 * @note Mendiane is a resource that can be found on the map
 * @note Herited from ARock class
*/
class Mendiane : public gui::ARock {
    public:
        Mendiane(std::uint32_t rockQuantity = 0 ) : gui::ARock( rockQuantity ) {};
};
