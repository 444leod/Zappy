/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** AAnimation
*/

#pragma once

#include "ILibrary.hpp"

namespace gui {
    class AAnimation {
        public:
            AAnimation(float duration, uint32_t frameCount, std::string name) : _duration(duration), _name(name), _frameCount(frameCount) {};
            ~AAnimation() = default;

            virtual void update(float deltaTime) = 0;
            virtual void draw(ILibrary& lib) = 0;

            void setDuration(float duration) { _duration = duration; }
            void setLoop(bool loop) { _loop = loop; }
            virtual float remainingTime() { return _duration; }
            virtual std::string name() { return _name; }

        protected:
            float _duration = 0;
            const std::string _name = "";
            uint32_t _frameCount;
            float _passedTime = 0;
            bool _loop = false;
            uint32_t _currentFrame = 0;
    };
}
