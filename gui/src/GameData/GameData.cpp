/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GameData
*/

#include "GameData.hpp"

namespace gui {
    void GameData::addPlayer(std::shared_ptr<Character> player)
    {
        this->_players.push_back(player);
        this->_map.getTileContentByCoordinates(player->position()).addEntity(player);
    }

    void GameData::removePlayer(std::uint32_t playerId)
    {
        for (auto it = this->_players.begin(); it != this->_players.end(); it++) {
            if ((*it)->id() == playerId) {
                this->_map.removeEntityFromTile((*it)->position(), playerId);
                this->_players.erase(it);
                return;
            }
        }
    }

    void GameData::addEgg(std::shared_ptr<Egg> egg)
    {
        this->_eggs.push_back(egg);
        this->_map.getTileContentByCoordinates(egg->position()).addEntity(egg);
    }

    void GameData::removeEgg(std::uint32_t eggId)
    {
        for (auto it = this->_eggs.begin(); it != this->_eggs.end(); it++) {
            if ((*it)->id() == eggId) {
                this->_map.removeEntityFromTile((*it)->position(), eggId);
                this->_eggs.erase(it);
                return;
            }
        }
    }
}
