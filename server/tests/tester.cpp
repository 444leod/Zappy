/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** tester
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include "Test.hpp"

int main(int argc, char const *argv[])
{
    Tester tester("./zappy_server");

    tester.addTest("Valid parameters 1", {"-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "team2", "team3", "team4", "-c", "1", "-f", "100"}, "", "", 0, std::chrono::seconds(1));
    tester.addTest("Valid parameters 2", {"-p", "10000", "-x", "20", "-y", "20", "-n", "name1", "name2", "name3", "-c", "3", "-f", "100"}, "", "", 0, std::chrono::seconds(1));

    tester.addTest("Not enought parameters (1)", {"-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c", "1", "-f"}, "", "Not enough parameters.\n", 84, std::chrono::seconds(1));
    tester.addTest("Not enought parameters (2)", {"-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c", "1"}, "", "Not enough parameters.\n", 84, std::chrono::seconds(1));
    tester.addTest("Not enought parameters (3)", {"-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c"}, "", "Not enough parameters.\n", 84, std::chrono::seconds(1));
    tester.addTest("Not enought parameters (4)", {"-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "team2"}, "", "Not enough parameters.\n", 84, std::chrono::seconds(1));
    tester.addTest("Not enought parameters (5)", {"-p", "4242", "-x", "10", "-y", "10", "-n", "team1"}, "", "Not enough parameters.\n", 84, std::chrono::seconds(1));
    tester.addTest("Not enought parameters (6)", {"-p", "4242", "-x", "10", "-y", "10", "-n"}, "", "Not enough parameters.\n", 84, std::chrono::seconds(1));
    tester.addTest("Not enought parameters (7)", {"-p", "4242", "-x", "10", "-y", "10"}, "", "Not enough parameters.\n", 84, std::chrono::seconds(1));
    tester.addTest("Not enought parameters (8)", {"-p", "4242", "-x", "10", "-y"}, "", "Not enough parameters.\n", 84, std::chrono::seconds(1));
    tester.addTest("Not enought parameters (9)", {"-p", "4242", "-x", "10"}, "", "Not enough parameters.\n", 84, std::chrono::seconds(1));
    tester.addTest("Not enought parameters (10)", {"-p", "4242", "-x"}, "", "Not enough parameters.\n", 84, std::chrono::seconds(1));
    tester.addTest("Not enought parameters (11)", {"-p", "4242"}, "", "Not enough parameters.\n", 84, std::chrono::seconds(1));
    tester.addTest("Not enought parameters (12)", {"-p"}, "", "Not enough parameters.\n", 84, std::chrono::seconds(1));
    tester.addTest("Not enought parameters (13)", {}, "", "Not enough parameters.\n", 84, std::chrono::seconds(1));

    tester.addTest("Invalid port (string)", {"-p", "port", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c", "1", "-f", "100"}, "", "Invalid port.\n", 84, std::chrono::seconds(1));
    tester.addTest("Invalid port (negative)", {"-p", "-1", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c", "1", "-f", "100"}, "", "Invalid port.\n", 84, std::chrono::seconds(1));
    tester.addTest("Invalid port (too big)", {"-p", "65536", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c", "1", "-f", "100"}, "", "Invalid port.\n", 84, std::chrono::seconds(1));

    tester.addTest("Invalid width (string)", {"-p", "4242", "-x", "width", "-y", "10", "-n", "team1", "team2", "-c", "1", "-f", "100"}, "", "Invalid width.\n", 84, std::chrono::seconds(1));
    tester.addTest("Invalid width (negative)", {"-p", "4242", "-x", "-1", "-y", "10", "-n", "team1", "team2", "-c", "1", "-f", "100"}, "", "Invalid width (min 2).\n", 84, std::chrono::seconds(1));
    tester.addTest("Invalid width (0)", {"-p", "4242", "-x", "0", "-y", "10", "-n", "team1", "team2", "-c", "1", "-f", "100"}, "", "Invalid width (min 2).\n", 84, std::chrono::seconds(1));
    tester.addTest("Invalid width (1)", {"-p", "4242", "-x", "1", "-y", "10", "-n", "team1", "team2", "-c", "1", "-f", "100"}, "", "Invalid width (min 2).\n", 84, std::chrono::seconds(1));

    tester.addTest("Invalid height (string)", {"-p", "4242", "-x", "10", "-y", "height", "-n", "team1", "team2", "-c", "1", "-f", "100"}, "", "Invalid height.\n", 84, std::chrono::seconds(1));
    tester.addTest("Invalid height (negative)", {"-p", "4242", "-x", "10", "-y", "-1", "-n", "team1", "team2", "-c", "1", "-f", "100"}, "", "Invalid height (min 2).\n", 84, std::chrono::seconds(1));
    tester.addTest("Invalid height (0)", {"-p", "4242", "-x", "10", "-y", "0", "-n", "team1", "team2", "-c", "1", "-f", "100"}, "", "Invalid height (min 2).\n", 84, std::chrono::seconds(1));
    tester.addTest("Invalid height (1)", {"-p", "4242", "-x", "10", "-y", "1", "-n", "team1", "team2", "-c", "1", "-f", "100"}, "", "Invalid height (min 2).\n", 84, std::chrono::seconds(1));

    tester.addTest("Invalid team name (not enough)", {"-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "-c", "1", "-f", "100", "-f", "100"}, "", "Invalid team names (min 2).\n", 84, std::chrono::seconds(1));
    tester.addTest("Invalid team name (non alphanum)", {"-p", "4242", "-x", "10", "-y", "10", "-n", "team1!", "team2ééé", "-c", "1", "-f", "100"}, "", "Invalid team name.\n", 84, std::chrono::seconds(1));
    tester.addTest("Invalid team name (duplicate)", {"-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "team1", "-c", "1", "-f", "100"}, "", "Duplicate team names.\n", 84, std::chrono::seconds(1));

    tester.addTest("Invalid client number (string)", {"-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c", "client", "-f", "100"}, "", "Invalid clientsNb.\n", 84, std::chrono::seconds(1));
    tester.addTest("Invalid client number (negative)", {"-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c", "-1", "-f", "100"}, "", "Invalid clientsNb (min 1).\n", 84, std::chrono::seconds(1));
    tester.addTest("Invalid client number (0)", {"-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c", "0", "-f", "100"}, "", "Invalid clientsNb (min 1).\n", 84, std::chrono::seconds(1));

    tester.addTest("Invalid frequency (string)", {"-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c", "1", "-f", "freq"}, "", "Invalid freq.\n", 84, std::chrono::seconds(1));
    tester.addTest("Invalid frequency (negative)", {"-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c", "1", "-f", "-1"}, "", "Invalid freq (min 1).\n", 84, std::chrono::seconds(1));
    tester.addTest("Invalid frequency (0)", {"-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c", "1", "-f", "0"}, "", "Invalid freq (min 1).\n", 84, std::chrono::seconds(1));

    tester.addTest("Wondering arguments (1)", {"-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c", "1", "-f", "100", "-f", "100"}, "", "Wondering arguments.\n", 84, std::chrono::seconds(1));
    tester.addTest("Wondering arguments (2)", {"-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c", "1", "-f", "100", "-c", "1"}, "", "Wondering arguments.\n", 84, std::chrono::seconds(1));
    tester.addTest("Wondering arguments (3)", {"-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c", "1", "-f", "100", "-n", "10"}, "", "Wondering arguments.\n", 84, std::chrono::seconds(1));

    tester.test();
    return 0;
}

