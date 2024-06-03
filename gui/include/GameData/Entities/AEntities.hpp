/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AEntities
*/

#ifndef AENTITIES_HPP_
#define AENTITIES_HPP_

#include <cstdint>
#include "Orientation.hpp"
#include "Vector.hpp"

/**
 * @brief Class representing entities in the simulation
 * @note Entities are the characters and the eggs in the simulation
 * @note Herited from AEntities class
*/
class AEntities {
    public:
        /**
         * @brief Construct a new AEntities object
        */
        AEntities() = default;

        /**
         * @brief Destroy the AEntities object
        */
        ~AEntities() = default;

        /**
         * @brief Set the entities Id
         * @param id Id of the entities
        */
        virtual void setEntitiesId(std::uint32_t id) { _id = id; };

        /**
         * @brief Get the entities Id
         * @return std::uint32_t Id of the entities
        */
        virtual std::uint32_t entitiesId() const { return _id; };

        /**
         * @brief Set the orientation of the entities
         * @param orientation Orientation of the entities
         * @note The orientation can be NORTH, EAST, SOUTH, WEST
        */
        virtual void setOrientation(Orientation orientation) { _orientation = orientation; };

        /**
         * @brief Get the orientation of the entities
         * @return Orientation Orientation of the entities
        */
        virtual Orientation orientation() const { return _orientation; };

        /**
         * @brief Set the position of the entities
         * @param position Position of the entities
        */
        virtual void setEntitiesPosition(Vector2i position) { _position = position; };

        /**
         * @brief Get the position of the entities
         * @return Vector2i Position of the entities
        */
        virtual Vector2i entitiesPosition() const { return _position; };

    protected:
        Vector2i _position = {0, 0};
        Orientation _orientation = Orientation::NORTH;
        std::uint32_t _id = 0;
};

#endif /* !AENTITIES_HPP_ */
