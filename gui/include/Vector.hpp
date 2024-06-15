/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Vector
*/

#pragma once

#include <cmath>
#include <iostream>

namespace gui {
    template<typename T>
    class Vector2 {
        public:
            Vector2() = default;
            Vector2(T x, T y) : _x(x), _y(y) {}
            Vector2(const Vector2& other) : _x(other.x()), _y(other.y()) {}
            Vector2(const Vector2&& other) : _x(other.x()), _y(other.y()) {}
            ~Vector2() = default;
            const Vector2<T>& operator=(const Vector2<T>& other) {
                this->_x = other.x();
                this->_y = other.y();
                return *this;
            }

            T x() const { return this->_x; }   // Getters
            T y() const { return this->_y; }
            void setX(T x) { this->_x = x; }   // Setters
            void setY(T y) { this->_y = y; }

            // Operators
            Vector2<T> operator+(const Vector2<T>& other) const {
                return Vector2<T>(this->_x + other._x, this->_y + other._y); }
            Vector2<T> operator-(const Vector2<T>& other) const {
                return Vector2<T>(this->_x - other._x, this->_y - other._y); }
            Vector2<T> operator*(const Vector2<T>& other) const {
                return Vector2<T>(this->_x * other._x, this->_y * other._y); }
            Vector2<T> operator/(const Vector2<T>& other) const {
                return Vector2<T>(this->_x / other._x, this->_y / other._y); }

            template<typename U>
            Vector2<T> operator*(U factor) const {
                return Vector2<T>(this->_x * factor, this->_y * factor); }
            template<typename U>
            Vector2<T> operator/(U factor) const {
                return Vector2<T>(this->_x / factor, this->_y / factor); }

            //More operators
            void operator+=(const Vector2<T>& other) {
                this->_x += other._x; this->_y += other._y; }
            void operator-=(const Vector2<T>& other) {
                this->_x -= other._x; this->_y -= other._y; }
            void operator*=(const Vector2<T>& other) {
                this->_x *= other._x; this->_y *= other._y; }
            void operator/=(const Vector2<T>& other) {
                this->_x /= other._x; this->_y /= other._y; }

            template<typename U>
            void operator*=(U factor) {
                this->_x *= factor; this->_y *= factor; }
            template<typename U>
            void operator/=(U factor) {
                this->_x /= factor; this->_y /= factor; }

            T distance(const Vector2<T>& other) const {
                T dx = _x - other._x;
                T dy = _y - other._y;
                return std::sqrt(dx * dx + dy * dy);
            }

            bool operator==(const Vector2<T>& other) const { return distance(other) < 0.001; }

            bool operator!=(const Vector2<T>& other) const { return !(*this == other); }

            bool operator<(const Vector2<T>& other) const { return this->_x < other._x && this->_y < other._y; }

        protected:
        private:
            T _x = .0; // .0 so that the compiler knows it's double-sized
            T _y = .0;
    };

    using Vector2d = Vector2<double>;
    using Vector2i = Vector2<int>;
    using Vector2f = Vector2<float>;
    using Vector2u = Vector2<unsigned int>;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const gui::Vector2<T>& vector)
{
    stream << "(" << vector.x() << ", " << vector.y() << ")";
    return stream;
}
