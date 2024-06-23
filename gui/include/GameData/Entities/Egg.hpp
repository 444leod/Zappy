/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Egg
*/

#pragma once

#include "AEntity.hpp"
#include "ILibrary.hpp"
#include "SkinsConfig.hpp"

namespace gui {
    /**
     * @brief Class representing an egg in the simulation
     * @note Egg is a resource that can be found on the map
     * @note Herited from AEntity class
    */
    class Egg : public AEntity {
        public:
            Egg() = delete;

            Egg(std::uint32_t id, Vector2u position, std::string teamName)
                : AEntity(id, position, teamName) { _skin = "egg"; }

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

            void updateAnimation(float deltaTime) override;
            void drawAnimation(ILibrary &lib) override;

        private:
            bool _hatched = false;
            bool _isDead = false;
            gui::AEntity::EntityType _type = gui::AEntity::EntityType::EGG;
            float _passedTime = 0;
            uint16_t _currentFrame = 0;
            uint16_t _frameCount = gui::skins::ANIMATIONS_FRAMES[gui::skins::SKINS::EGG][0].second;
    };
}
