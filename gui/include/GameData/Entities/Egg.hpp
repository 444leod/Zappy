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

            Egg(std::uint32_t id, Vector2u position, std::string teamName)
                : AEntity(id, position, teamName) {}

            ~Egg() = default;

            /**
             * @brief set the hatched value
             * @param hatched The hatched value
            */
            void hatch() { this->_hatched = true; }

            /**
             * @brief Set the egg life status
             * @param isDead The egg life status
            */
            void kill() { this->_isDead = true; }

        private:
            bool _hatched = false;
            bool _isDead = false;
    };
}
