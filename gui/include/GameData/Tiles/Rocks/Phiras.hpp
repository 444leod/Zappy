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
namespace gui {
    class Phiras : public ARock {
        public:
            Phiras(std::uint32_t rockQuantity = 0 ) : ARock( rockQuantity ) {};
    };
}
