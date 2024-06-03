/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ARock
*/

#pragma once

#include <cstdint>

namespace gui {
    /**
     * @brief Abstract class representing a rock in the simulation
     * @note Rock is a resource that can be found on the map
    */
    class ARock {
        public:
            ARock(std::uint32_t rockQuantity = 0) : _rockQuantity(rockQuantity) {};
            ~ARock() = default;

            virtual void addRock(std::uint32_t quantity) { _rockQuantity += quantity; };
            virtual void removeRock(std::uint32_t quantity) { _rockQuantity -= quantity; };

            virtual void setRockQuantity(std::uint32_t quantity) { _rockQuantity = quantity; };
            virtual std::uint32_t rockQuantity() const { return _rockQuantity; };

        protected:
            std::uint32_t _rockQuantity;
    };
}
