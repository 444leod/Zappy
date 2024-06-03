/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Message
*/

#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <vector>
#include <iostream>
#include <cstdint>

class Message {
    public:
        /**
         * @brief Push a message to the message list
         * @param time The time of the message
         * @param message The message*
         *
         * @note The message is pushed to the message list
         * @note The message is a pair of time and message
        */
        void addMessage(std::uint32_t time, std::string message) {
            _messages.push_back(std::make_pair(time, message));
        }

        /**
         * @brief Get the size of the message list
         * @return std::size_t The size of the message list
        */
        std::size_t messagesSize() const {
            return _messages.size();
        }

        /**
         * @brief Get a message from the message list
         * @param index The index of the message
         * @return std::pair<std::uint32_t, std::string> The message
        */
        std::pair<std::uint32_t, std::string> message(std::size_t index) const {
            return _messages[index];
        }

        /**
         * @brief Clear the message list
        */
        void clearMessages() {
            _messages.clear();
        }

    private:
        std::vector<std::pair<std::uint32_t, std::string>> _messages;
};

#endif /* !MESSAGE_HPP_ */
