/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Rock
*/

#ifndef ROCK_HPP_
#define ROCK_HPP_

/**
 * @brief Class representing all rocks available in the simulation
 * @note The rock is a resource that can be found on the map
 * @note The rock can contain linemate, deraumere, sibur, mendiane, phiras, thystame
*/
class Rock {
    public:
        /**
         * @brief Construct a new Rock object
        */
        Rock() = default;

        /**
         * @brief Construct a new Rock object
         * @param linemate The linemate of the rock
         * @param deraumere The deraumere of the rock
         * @param sibur The sibur of the rock
         * @param mendiane The mendiane of the rock
         * @param phiras The phiras of the rock
         * @param thystame The thystame of the rock
        */
        Rock(int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
        {
            _linemate = linemate;
            _deraumere = deraumere;
            _sibur = sibur;
            _mendiane = mendiane;
            _phiras = phiras;
            _thystame = thystame;
        }

        /**
         * @brief Destroy the Rock object
        */
        ~Rock() = default;

        /**
         * @brief Get the number of linemate
         * @return int The number of linemate
        */
        int getLinemate() { return _linemate; }

        /**
         * @brief Set the number of linemate
         * @param linemate The number of linemate
        */
        void setLinemate(int linemate) { _linemate = linemate; }

        /**
         * @brief Get the number of deraumere
         * @return int The number of deraumere
        */
        int getDeraumere() { return _deraumere; }

        /**
         * @brief Set the number of deraumere
         * @param deraumere The number of deraumere
        */
        void setDeraumere(int deraumere) { _deraumere = deraumere; }

        /**
         * @brief Get the number of sibur
         * @return int The number of sibur
        */
        int getSibur() { return _sibur; }

        /**
         * @brief Set the number of sibur
         * @param sibur The number of sibur
        */
        void setSibur(int sibur) { _sibur = sibur; }

        /**
         * @brief Get the number of mendiane
         * @return int The number of mendiane
        */
        int getMendiane() { return _mendiane; }

        /**
         * @brief Set the number of mendiane
         * @param mendiane The number of mendiane
        */
        void setMendiane(int mendiane) { _mendiane = mendiane; }

        /**
         * @brief Get the number of phiras
         * @return int The number of phiras
        */
        int getPhiras() { return _phiras; }

        /**
         * @brief Set the number of phiras
         * @param phiras The number of phiras
        */
        void setPhiras(int phiras) { _phiras = phiras; }

        /**
         * @brief Get the number of thystame
         * @return int The number of thystame
        */
        int getThystame() { return _thystame; }

        /**
         * @brief Set the number of thystame
         * @param thystame The number of thystame
        */
        void setThystame(int thystame) { _thystame = thystame; }

    private:
        int _linemate = 0;
        int _deraumere = 0;
        int _sibur = 0;
        int _mendiane = 0;
        int _phiras = 0;
        int _thystame = 0;
};

#endif /* !ROCK_HPP_ */
