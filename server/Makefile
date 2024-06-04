##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

__GREEN=\033[0;32m
__NC=\033[0m

__INFO = ${__GREEN}[INFO]${__NC}

__NAME = zappy_server
__LIBMY = libmy.a
__LIBNETWORK = libnetwork.a

__TESTER_NAME = tester

__SRC = $(addprefix src/, $(__SRC_SRC)) \
	$(addprefix src/args/, $(__SRC_ARGS)) \
	$(addprefix src/commands/, $(__SRC_COMMANDS)) \
	$(addprefix src/commands/ai/, $(__SRC_AI)) \
	$(addprefix src/commands/graphical/, $(__SRC_GRAPHICAL)) \
	$(addprefix src/network/, $(__SRC_NETWORK)) \
	$(addprefix src/network/client/, $(__SRC_CLIENT)) \
	main.c

__SRC_SRC := server.c \
	exit.c \
	handle_clients.c \
	handle_commands.c

__SRC_COMMANDS := commands.c \
	unknown_command.c \

__SRC_AI := forward.c \

__SRC_GRAPHICAL := msz.c \

__SRC_ARGS := params.c \
	check_args.c \
	init_server_info.c \
	display_help.c \

__SRC_ARGS := params.c \
	check_args.c \
	init_server_info.c \
	display_help.c \

__SRC_NETWORK := global_packet_send.c \
	send_packets.c \
	special_print.c \

__SRC_CLIENT := add_client.c \
	clear_clients.c \
	create_client.c \
	get_clients.c \
	remove_client.c \

__SRC_TEST := tests/tester.cpp \
	tests/Test.cpp

%.o: %.c
	@$(__CC) -c -o $@ $< $(__CFLAGS)

%.o: %.cpp
	@g++ -c -o $@ $< -std=c++20

__OBJ = $(__SRC:.c=.o)

__TEST_OBJ = $(__SRC_TEST:.cpp=.o)

__CC = gcc

__CFLAGS = -Wall -Wextra -Werror -Wpedantic -I./include -L. -lmy -lnetwork

all: $(__LIBMY) $(__LIBNETWORK) $(__NAME)
	@echo -ne "\n${__INFO} Server compiled successfully.${__NC}\n"

$(__NAME): $(__OBJ)
	@$(__CC) -o $(__NAME) $(__OBJ) $(__CFLAGS)

$(__LIBMY):
	@make -C ./lib -s

$(__LIBNETWORK):
	@make -C ./lib -s

clean:
	@make clean -C ./lib -s
	@rm -f $(__OBJ)
	@echo -ne "\n${__INFO} Server cleaned.${__NC}\n"

fclean: clean
	@make fclean -C ./lib -s
	@rm -f $(__NAME)
	@echo -ne "\n${__INFO} Server fully cleaned.${__NC}\n"

re: fclean all

$(__TESTER_NAME): $(__TEST_OBJ)
	@g++ -o $(__TESTER_NAME) $(__TEST_OBJ) -std=c++20

tests_run: $(__TESTER_NAME) all
	@./$(__TESTER_NAME)

debug:
	@make debug -C ./lib -s
	@$(__CC) -g -o $(__NAME) $(__SRC) $(__CFLAGS)
	@echo -ne "\n${__INFO} Debug mode compiled successfully.${__NC}\n"

dev:
	@make dev -C ./lib -s
	@$(__CC) -g -o $(__NAME) $(__SRC) $(__CFLAGS) -DDEV_MODE
	@echo -ne "\n${__INFO} Dev mode compiled successfully.${__NC}\n"

.PHONY: all clean fclean re
.SILENT: run
