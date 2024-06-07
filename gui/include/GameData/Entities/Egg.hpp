/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Egg
*/

#pragma once

#include "AEntity.hpp"

namespace gui {
    /**
     * @brief Class representing an egg in the simulation
     * @note Egg is a resource that can be found on the map
     * @note Herited from AEntity class
    */
    class Egg : public AEntity {
        public:
            Egg() = default;
            ~Egg() = default;
    };
}