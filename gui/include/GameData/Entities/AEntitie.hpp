/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AEntitie
*/

#pragma once

#include <cstdint>
#include "Orientation.hpp"
#include "Vector.hpp"

/**
 * @brief Class representing entitie in the simulation
 * @note Entitie are the characters and the eggs in the simulation
 * @note Herited from AEntitie class
*/
class AEntitie {
    public:
        /**
         * @brief Construct a new AEntitie object
        */
        AEntitie() = default;

        /**
         * @brief Destroy the AEntitie object
        */
        ~AEntitie() = default;

        /**
         * @brief Set the entitie Id
         * @param id Id of the entitie
        */
        virtual void setEntitieId(std::uint32_t id) { _id = id; };

        /**
         * @brief Get the entitie Id
         * @return std::uint32_t Id of the entitie
        */
        virtual std::uint32_t entitieId() const { return _id; };

        /**
         * @brief Set the orientation of the entitie
         * @param orientation Orientation of the entitie
         * @note The orientation can be NORTH, EAST, SOUTH, WEST
        */
        virtual void setOrientation(Orientation orientation) { _orientation = orientation; };

        /**
         * @brief Get the orientation of the entitie
         * @return Orientation Orientation of the entitie
        */
        virtual Orientation orientation() const { return _orientation; };

        /**
         * @brief Set the position of the entitie
         * @param position Position of the entitie
        */
        virtual void setEntitiePosition(Vector2i position) { _position = position; };

        /**
         * @brief Get the position of the entitie
         * @return Vector2i Position of the entitie
        */
        virtual Vector2i entitiePosition() const { return _position; };

    protected:
        Vector2i _position = {0, 0};
        Orientation _orientation = Orientation::NORTH;
        std::uint32_t _id = 0;
};
