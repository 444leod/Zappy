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
__TEST = server_suite
__TESTER_NAME = tester
__LIBMY = libmy.a
__LIBNETWORK = libnetwork.a


# =============================================================================
# Server code sources
# =============================================================================


__ASRC = $(__SRC) \
	main.c

__SRC	=	$(addprefix src/, $(__SRC_SRC)) \
	$(addprefix src/args/, $(__SRC_ARGS)) \
	$(addprefix src/commands/, $(__SRC_COMMANDS)) \
	$(addprefix src/commands/ai/, $(__SRC_AI)) \
	$(addprefix src/commands/graphical/, $(__SRC_GRAPHICAL)) \
	$(addprefix src/network/, $(__SRC_NETWORK)) \
	$(addprefix src/network/client/, $(__SRC_CLIENT)) \

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


# =============================================================================
# Unit tests sources
# =============================================================================

__TEST_SRC	=	$(__SRC) \
	$(addprefix ../tests/server/, $(__SRC_ROOT_TEST)) \
	$(addprefix ../tests/server/lib/my/, $(__SRC_LIB_MY_TEST))

__SRC_ROOT_TEST := utils.c \
	client.c

__SRC_LIB_MY_TEST := escaped_string.c \
	garbage_collector.c \
	is_alphanum.c \
	is_number.c \
	my_snprintf.c \
	linked_list.c \
	my_strdup.c \
	replace_char.c \
	supercat.c \
	tablen.c \
	str_to_word_array.c \


# =============================================================================
# Functionnal tests sources
# =============================================================================

__TESTER_SRC := tests/tester.cpp \
	tests/Test.cpp


# =============================================================================
# Compilation flags
# =============================================================================


__CC = gcc
__CFLAGS += -Wall -Wextra -Werror -Wpedantic -I./include -L. -lmy -lnetwork
__TEST_FLAGS = $(__CFLAGS) --coverage -lcriterion -I../tests

%.o: %.c
	@$(__CC) -c -o $@ $< $(__CFLAGS)


# =============================================================================
# Objects
# =============================================================================


__OBJ = $(__ASRC:.c=.o)
__TEST_OBJ = $(__TEST_SRC:.c=.o)
__TESTER_OBJ = $(__TESTER_SRC:.cpp=.o)

%.o: %.cpp
	@g++ -c -o $@ $< -std=c++20


# =============================================================================
# Basic rules
# =============================================================================


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


# =============================================================================
# Tests rules
# =============================================================================


$(__TESTER_NAME): all $(__TESTER_OBJ)
	@g++ -o $(__TESTER_NAME) $(__TESTER_OBJ) -std=c++20 -DSILENT



tests_run: $(__TESTER_NAME) $(__LIBMY) $(__LIBNETWORK)
	@./$(__TESTER_NAME)
	@gcc -o $(__TEST) $(__TEST_SRC) $(__TEST_FLAGS)
	@./$(__TEST)

tests_clean:
	@make fclean -i -C ./lib -s
	@rm -f $(__NAME)
	@rm -f $(__OBJ)
	@rm -f $(__TESTER_NAME)
	@rm -f $(__TESTER_OBJ)
	@rm -f $(__TEST)
	@rm -f $(__TEST_OBJ)
	@find . -name "*.gcda" -delete
	@find . -name "*.gcno" -delete

unit_tests_run: $(__LIBMY) $(__LIBNETWORK) $(__NAME)
	@gcc -o $(__TEST) $(__TEST_SRC) $(__TEST_FLAGS)
	@./$(__TEST)


# =============================================================================
# Custom rules
# =============================================================================


debug:
	@make debug -C ./lib -s
	@$(__CC) -g -o $(__NAME) $(__ASRC) $(__CFLAGS)
	@echo -ne "\n${__INFO} Debug mode compiled successfully.${__NC}\n"

dev:
	@make dev -C ./lib -s
	@$(__CC) -g -o $(__NAME) $(__ASRC) $(__CFLAGS) -DDEV_MODE
	@echo -ne "\n${__INFO} Dev mode compiled successfully.${__NC}\n"

.PHONY: all clean fclean re
.SILENT: run
