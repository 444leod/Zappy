/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** SkinsConfig
*/

#pragma once

#include <map>
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>

namespace gui::skins {
    enum class SKINS {
        BOWLER,
        ELECTRO,
        GOBLINBD,
        GOBLIN,
        HOG,
        ICE_WIZARD,
        KNIGHT,
        EGG
    };

    inline std::unordered_map<SKINS, std::string> SKIN_TO_STRING = {
        {SKINS::BOWLER, "bowler"},
        {SKINS::ELECTRO, "electro"},
        {SKINS::GOBLINBD, "goblinBD"},
        {SKINS::GOBLIN, "goblin"},
        {SKINS::HOG, "hog"},
        {SKINS::ICE_WIZARD, "ice_wizard"},
        {SKINS::KNIGHT, "knight"},
        {SKINS::EGG, "egg"}
    };

    inline std::unordered_map<std::string, SKINS> STRING_TO_SKIN = {
        {"bowler", SKINS::BOWLER},
        {"electro", SKINS::ELECTRO},
        {"goblinBD", SKINS::GOBLINBD},
        {"goblin", SKINS::GOBLIN},
        {"hog", SKINS::HOG},
        {"ice_wizard", SKINS::ICE_WIZARD},
        {"knight", SKINS::KNIGHT},
        {"egg", SKINS::EGG}
    };

    inline std::map<SKINS, std::string> SKIN_TO_FILE = {
        {SKINS::BOWLER, "bowlerSpriteSheet.png"},
        {SKINS::ELECTRO, "electroSpriteSheet.png"},
        {SKINS::GOBLINBD, "goblinBDSpriteSheet.png"},
        {SKINS::GOBLIN, "goblinSpriteSheet.png"},
        {SKINS::HOG, "hogSpriteSheet.png"},
        {SKINS::ICE_WIZARD, "iceWizardSpriteSheet.png"},
        {SKINS::KNIGHT, "knightSpriteSheet.png"},
        {SKINS::EGG, "eggSpriteSheet.png"}
    };

    enum class ANIMATIONS {
        EJECT_SOUTH,
        EJECT_WEST,
        EJECT_EAST,
        EJECT_NORTH,
        WALK_SOUTH,
        WALK_WEST,
        WALK_EAST,
        WALK_NORTH,
        INCANTATION,
        ECLOSION
    };

    inline std::unordered_map<ANIMATIONS, std::string> ANIMATION_TO_STRING = {
        {ANIMATIONS::EJECT_SOUTH, "_eject_south_"},
        {ANIMATIONS::EJECT_WEST, "_eject_west_"},
        {ANIMATIONS::EJECT_EAST, "_eject_east_"},
        {ANIMATIONS::EJECT_NORTH, "_eject_north_"},
        {ANIMATIONS::WALK_SOUTH, "_walk_south_"},
        {ANIMATIONS::WALK_WEST, "_walk_west_"},
        {ANIMATIONS::WALK_EAST, "_walk_east_"},
        {ANIMATIONS::WALK_NORTH, "_walk_north_"},
        {ANIMATIONS::INCANTATION, "_incantation_"},
        {ANIMATIONS::ECLOSION, "_eclosion_"}
    };

    enum class STATIC_SPRITES {
        SOUTH,
        WEST,
        EAST,
        NORTH
    };

    inline std::unordered_map<STATIC_SPRITES, std::string> STATIC_SPRITES_TO_STRING = {
        {STATIC_SPRITES::SOUTH, "_south"},
        {STATIC_SPRITES::WEST, "_west"},
        {STATIC_SPRITES::EAST, "_east"},
        {STATIC_SPRITES::NORTH, "_north"}
 };

    inline std::unordered_map<SKINS, std::vector<std::pair<ANIMATIONS, std::uint16_t>>> ANIMATIONS_FRAMES = {
        {SKINS::BOWLER, {
            {ANIMATIONS::EJECT_SOUTH, 13},
            {ANIMATIONS::EJECT_WEST, 13},
            {ANIMATIONS::EJECT_EAST, 13},
            {ANIMATIONS::EJECT_NORTH, 13},
            {ANIMATIONS::WALK_SOUTH, 13},
            {ANIMATIONS::WALK_WEST, 13},
            {ANIMATIONS::WALK_EAST, 13},
            {ANIMATIONS::WALK_NORTH, 13},
            {ANIMATIONS::INCANTATION, 12}
        }},
        {SKINS::ELECTRO, {
            {ANIMATIONS::EJECT_SOUTH, 7},
            {ANIMATIONS::EJECT_WEST, 7},
            {ANIMATIONS::EJECT_EAST, 7},
            {ANIMATIONS::EJECT_NORTH, 7},
            {ANIMATIONS::WALK_SOUTH, 8},
            {ANIMATIONS::WALK_WEST, 8},
            {ANIMATIONS::WALK_EAST, 8},
            {ANIMATIONS::WALK_NORTH, 8},
            {ANIMATIONS::INCANTATION, 16}
        }},
        {SKINS::GOBLINBD, {
            {ANIMATIONS::EJECT_SOUTH, 5},
            {ANIMATIONS::EJECT_WEST, 5},
            {ANIMATIONS::EJECT_EAST, 5},
            {ANIMATIONS::EJECT_NORTH, 5},
            {ANIMATIONS::WALK_SOUTH, 8},
            {ANIMATIONS::WALK_WEST, 8},
            {ANIMATIONS::WALK_EAST, 8},
            {ANIMATIONS::WALK_NORTH, 8},
            {ANIMATIONS::INCANTATION, 16}
        }},
                {SKINS::GOBLIN, {
            {ANIMATIONS::EJECT_SOUTH, 7},
            {ANIMATIONS::EJECT_WEST, 7},
            {ANIMATIONS::EJECT_EAST, 7},
            {ANIMATIONS::EJECT_NORTH, 7},
            {ANIMATIONS::WALK_SOUTH, 8},
            {ANIMATIONS::WALK_WEST, 8},
            {ANIMATIONS::WALK_EAST, 8},
            {ANIMATIONS::WALK_NORTH, 8},
            {ANIMATIONS::INCANTATION, 16}
        }},
        {SKINS::HOG, {
            {ANIMATIONS::EJECT_SOUTH, 10},
            {ANIMATIONS::EJECT_WEST, 10},
            {ANIMATIONS::EJECT_EAST, 10},
            {ANIMATIONS::EJECT_NORTH, 10},
            {ANIMATIONS::WALK_SOUTH, 8},
            {ANIMATIONS::WALK_WEST, 8},
            {ANIMATIONS::WALK_EAST, 8},
            {ANIMATIONS::WALK_NORTH, 8},
            {ANIMATIONS::INCANTATION, 16}
        }},
        {SKINS::ICE_WIZARD, {
            {ANIMATIONS::EJECT_SOUTH, 9},
            {ANIMATIONS::EJECT_WEST, 9},
            {ANIMATIONS::EJECT_EAST, 9},
            {ANIMATIONS::EJECT_NORTH, 9},
            {ANIMATIONS::WALK_SOUTH, 8},
            {ANIMATIONS::WALK_WEST, 8},
            {ANIMATIONS::WALK_EAST, 8},
            {ANIMATIONS::WALK_NORTH, 8},
            {ANIMATIONS::INCANTATION, 16}
        }},
        {SKINS::KNIGHT, {
            {ANIMATIONS::EJECT_SOUTH, 14},
            {ANIMATIONS::EJECT_WEST, 14},
            {ANIMATIONS::EJECT_EAST, 14},
            {ANIMATIONS::EJECT_NORTH, 14},
            {ANIMATIONS::WALK_SOUTH, 11},
            {ANIMATIONS::WALK_WEST, 12},
            {ANIMATIONS::WALK_EAST, 12},
            {ANIMATIONS::WALK_NORTH, 12},
            {ANIMATIONS::INCANTATION, 15}
        }},
        {SKINS::EGG, {
            {ANIMATIONS::ECLOSION, 9}
        }}
    };

    inline std::unordered_map<SKINS, std::vector<std::pair<STATIC_SPRITES, std::pair<std::uint16_t, std::uint16_t>>>> STATIC_SPRITES_POSITION = {
        {SKINS::BOWLER, {
            {STATIC_SPRITES::NORTH, {8, 0}},
            {STATIC_SPRITES::EAST, {8, 3}},
            {STATIC_SPRITES::SOUTH, {8, 6}},
            {STATIC_SPRITES::WEST, {8, 9}}
        }},
        {SKINS::ELECTRO, {
            {STATIC_SPRITES::NORTH, {8, 0}},
            {STATIC_SPRITES::EAST, {8, 4}},
            {STATIC_SPRITES::SOUTH, {8, 8}},
            {STATIC_SPRITES::WEST, {8, 12}}
        }},
        {SKINS::GOBLINBD, {
            {STATIC_SPRITES::NORTH, {8, 0}},
            {STATIC_SPRITES::EAST, {8, 4}},
            {STATIC_SPRITES::SOUTH, {8, 8}},
            {STATIC_SPRITES::WEST, {8, 12}}
        }},
        {SKINS::GOBLIN, {
            {STATIC_SPRITES::NORTH, {8, 0}},
            {STATIC_SPRITES::EAST, {8, 4}},
            {STATIC_SPRITES::SOUTH, {8, 8}},
            {STATIC_SPRITES::WEST, {8, 12}}
        }},
        {SKINS::HOG, {
            {STATIC_SPRITES::NORTH, {8, 0}},
            {STATIC_SPRITES::EAST, {8, 4}},
            {STATIC_SPRITES::SOUTH, {8, 8}},
            {STATIC_SPRITES::WEST, {8, 12}}
        }},
        {SKINS::ICE_WIZARD, {
            {STATIC_SPRITES::NORTH, {8, 0}},
            {STATIC_SPRITES::EAST, {8, 5}},
            {STATIC_SPRITES::SOUTH, {8, 8}},
            {STATIC_SPRITES::WEST, {8, 12}}
        }},
        {SKINS::KNIGHT, {
            {STATIC_SPRITES::NORTH, {8, 0}},
            {STATIC_SPRITES::EAST, {8, 3}},
            {STATIC_SPRITES::SOUTH, {8, 7}},
            {STATIC_SPRITES::WEST, {8, 1}}
        }}
    };
}
