/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** reply_codes
*/

#pragma once

typedef struct server_message_s {
    int code;
    char *message;
} server_message_t;

/*
    REPLY CODE

    2xx : Positive Completion reply
    5xx : Permanent Negative Completion reply

    x0x : Global
    x1x : User related
    x2x : Message related
    x3x : Team (user-side) related
    x4x : Team (server-side) related
    x5x : List related
    x6x : Info related
    x7x : Context related

*/

/**
 * @enum REPLY_CODES
 * @brief Enum of reply codes
 * @details Enum of reply codes with their corresponding code
*/
enum REPLY_CODES {
    COMMAND_OK = 200,
    HELP_MESSAGE = 201,

    USERS_LIST = 211,
    USER_INFO = 212,
    USER_CREATED = 213,
    USER_LOGGED_IN = 214,
    USER_LOGGED_OUT = 215,
    NEW_USER = 216,


    MESSAGE_SENT = 220,
    MESSAGE_RECEIVED = 221,
    MESSAGES_LIST = 222,
    THREAD_REPLY_RECEIVED = 223,

    TEAM_SUBSCRIBED = 230,
    TEAM_UNSUBSCRIBED = 231,
    NO_SUBSCRIBED_TEAMS = 232,

    TEAM_CREATED = 240,
    CHANNEL_CREATED = 241,
    THREAD_CREATED = 242,
    REPLY_CREATED = 243,

    TEAM_LIST = 250,
    CHANNEL_LIST = 251,
    THREAD_LIST = 252,
    REPLY_LIST = 253,

    CURRENT_USER_INFO = 260,
    TEAM_INFO = 261,
    CHANNEL_INFO = 262,
    THREAD_INFO = 263,

    GLOBAL_CONTEXT_SET = 270,
    TEAM_CONTEXT_SET = 271,
    CHANNEL_CONTEXT_SET = 272,
    THREAD_CONTEXT_SET = 273,
};

/**
 * @enum ERROR_CODES
 * @brief Enum of error codes
 * @details Enum of error codes with their corresponding code
*/
enum ERROR_CODES {
    SYNTAX_ERROR = 500,
    SYNTAX_ERROR_IN_PARAMETERS = 501,
    COMMAND_NOT_IMPLEMENTED = 502,
    BAD_COMMAND_SEQUENCE = 503,
    COMMAND_NOT_IMPLEMENTED_FOR_PARAMETER = 504,
    NAME_TOO_LONG = 506,
    DESCRIPTION_TOO_LONG = 507,
    BODY_TOO_LONG = 508,
    ALREADY_EXISTS = 509,

    UNSUFFICIENT_PERMISSIONS = 510,
    NOT_LOGGED_IN = 511,
    USER_ALREADY_LOGGED_IN = 512,
    ALREADY_LOGGED_IN = 513,
    ALREADY_LOGGED_OUT = 514,
    NOT_SUBSCRIBED = 515,
    ALREADY_SUBSCRIBED = 516,

    EMPTY_MESSAGE_LIST = 520,

    EMPTY_TEAM_LIST = 551,
    EMPTY_CHANNEL_LIST = 552,
    EMPTY_THREAD_LIST = 553,
    EMPTY_USER_LIST = 554,
    EMPTY_REPLY_LIST = 555,

    INEXISTANT_TEAM = 570,
    INEXISTANT_CHANNEL = 571,
    INEXISTANT_THREAD = 572,
    INEXISTANT_USER = 573,

    UNKNOWN_ERROR = 590,
};
