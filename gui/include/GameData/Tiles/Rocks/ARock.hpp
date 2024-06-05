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
            /**
             * @brief Construct a new ARock object
             * @param quantity Quantity of rock
            */
            ARock(std::uint32_t quantity = 0) : _quantity(quantity) {};

            /**
             * @brief Destroy the ARock object
            */
            ~ARock() = default;

            /**
             * @brief Add rock to the quantity
             * @param quantity Quantity of rock to add
            */
            virtual void addRock(std::uint32_t quantity) { this->_quantity += quantity; };

            /**
             * @brief Remove rock from the quantity
             * @param quantity Quantity of rock to remove
            */
            virtual void removeRock(std::uint32_t quantity) { this->_quantity -= quantity; };

            /**
             * @brief Set the rock quantity
             * @param quantity Quantity of rock
            */
            virtual void setQuantity(std::uint32_t quantity) { this->_quantity = quantity; };

            /**
             * @brief Get the rock quantity
             * @return std::uint32_t Quantity of rock
            */
            virtual std::uint32_t quantity() const { return this->_quantity; };

        protected:
            std::uint32_t _quantity;
    };
}
