/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ITextureManager
*/

#pragma once

#include "Color.hpp"
#include "Rect.hpp"

#include <string>
#include <variant>
#include <vector>
#include <optional>
#include <memory>
#include <map>

namespace gui {

    /**
     * @brief Represents the specification required to create a textual texture
     */
    struct TextureTextualSpecification {
        char character;
        Color color;
    };

    /**
     * @brief Represents an image for a texture
     */
    struct TextureImage {
        std::string path;
    };

    /**
     * @brief Represents the specification required to create a texture
     */
    struct TextureSpecification {
        TextureTextualSpecification textual;
        TextureImage graphical;
    };

    /**
     * @brief Represents a texture
     */
    class ITexture {
    public:
        virtual ~ITexture() = default;

        /**
         * @brief Returns the specification required to create the texture
         *
         * @return const TextureSpecification& The specification required to create the texture
         */
        virtual const TextureSpecification& specification() const = 0;
    };

    /**
     * @brief Represents a texture manager
     */
    class ITextureManager {
    public:
        virtual ~ITextureManager() = default;

        /**
         * @brief Loads a texture
         *
         * @param name the name of the texture
         * @param specification the specification required to create the texture
         * @param width the width of the texture
         * @param height the height of the texture
         * @return true if the texture has been loaded
         * @return false if the texture failed to load
         */
        virtual bool load(const std::string& name, const TextureSpecification& specification) = 0;

        /**
         * @brief Retrieves a texture
         *
         * @param name the name of the texture
         * @return ITexture& the texture
         */
        virtual std::shared_ptr<ITexture> get(const std::string& name) = 0;

        /**
         * @brief Retrieves all the textures specifications with their name
         *
         * @return std::vector<TextureSpecification> the specifications of all the textures
         */
        virtual std::map<std::string, TextureSpecification> dump() const = 0;
    };
}
