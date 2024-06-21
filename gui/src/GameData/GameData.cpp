/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GameData
*/

#include "GameData.hpp"
#include <algorithm>

namespace gui {
    void GameData::addPlayer(std::shared_ptr<Player> player)
    {
        this->_players.push_back(player);
        this->_map.at(player->position())->addEntity(player);
    }

    void GameData::removePlayer(std::uint32_t playerId)
    {
        auto it = std::find_if(this->_players.begin(), this->_players.end(),
            [playerId](const auto& player){ return player->id() == playerId; });

        if (it != this->_players.end()) {
            this->_map.at((*it)->position())->removeEntity(playerId);
            this->_players.erase(it);
        }
    }

    void GameData::addEgg(std::shared_ptr<Egg> egg)
    {
        this->_eggs.push_back(egg);
        this->_map.at(egg->position())->addEntity(egg);
    }

    void GameData::removeEgg(std::uint32_t eggId)
    {
        auto it = std::find_if(this->_eggs.begin(), this->_eggs.end(),
            [eggId](const auto& egg){ return egg->id() == eggId; });

        if (it != this->_eggs.end()) {
            this->_map.at((*it)->position())->removeEntity(eggId);
            this->_eggs.erase(it);
        }
    }

    bool GameData::playerExists(std::uint32_t playerId) const
    {
        auto it = std::find_if(this->_players.begin(), this->_players.end(),
            [playerId](const auto& player){ return player->id() == playerId; });

        return it != this->_players.end();
    }

    bool GameData::teamExists(const std::string& teamName) const
    {
        auto it = std::find_if(this->_teamNames.begin(), this->_teamNames.end(),
            [teamName](const auto& team){ return team == teamName; });

        return it != this->_teamNames.end();
    }

    bool GameData::eggExists(std::uint32_t eggId) const
    {
        auto it = std::find_if(this->_eggs.begin(), this->_eggs.end(),
            [eggId](const auto& egg){ return egg->id() == eggId; });

        return it != this->_eggs.end();
    }

    std::optional<std::shared_ptr<Player>> GameData::getPlayerById(std::uint32_t playerId) const
    {
        for (const auto &player : this->_players) {
            if (player->id() == playerId)
                return player;
        }
        return std::nullopt;
    }

    std::optional<std::shared_ptr<Egg>> GameData::getEggById(std::uint32_t eggId) const
    {
        for (const auto &egg : this->_eggs) {
            if (egg->id() == eggId)
                return egg;
        }
        return std::nullopt;
    }

    void GameData::teamWin(std::string teamName)
    {
        _teamLose = true;
        std::cout << "Team " << teamName << " win" << std::endl;
    }

    void GameData::teamDraw()
    {
        _isDraw = true;
        std::cout << "Draw" << std::endl;
    }

    void GameData::addTeamName(std::string teamName)
    {
        this->_teamNames.push_back(teamName);
        gui::Color randomColor = gui::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255, 255);

        bool isColorAlreadyUsed = true;
        while (isColorAlreadyUsed) {
            isColorAlreadyUsed = false;
            for (auto &color : this->_teamColors) {
                if (color.blue == randomColor.blue && color.red == randomColor.red && color.green == randomColor.green) {
                    randomColor = gui::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255, 255);
                    isColorAlreadyUsed = true;
                }
            }
        }
        this->_teamColors.push_back(randomColor);
        switch (this->_teamNames.size() % 7) {
            case 0:
                this->_teamSkins[teamName] = {"bowler", randomColor};
                break;
            case 1:
                this->_teamSkins[teamName] = {"bowler", randomColor};
                break;
            case 2:
                this->_teamSkins[teamName] = {"bowler", randomColor};
                break;
            case 3:
                this->_teamSkins[teamName] = {"bowler", randomColor};
                break;
            case 4:
                this->_teamSkins[teamName] = {"bowler", randomColor};
                break;
            case 5:
                this->_teamSkins[teamName] = {"bowler", randomColor};
                break;
            case 6:
                this->_teamSkins[teamName] = {"bowler", randomColor};
        }
    }

    std::pair<std::string, gui::Color> GameData::teamSkin(const std::string &teamName) const
    {
        return this->_teamSkins.at(teamName);
    }
}
