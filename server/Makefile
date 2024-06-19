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
	$(addprefix src/game/, $(__SRC_GAME)) \
	$(addprefix src/commands/graphical/, $(__SRC_GRAPHICAL)) \
	$(addprefix src/network/, $(__SRC_NETWORK)) \
	$(addprefix src/network/client/, $(__SRC_CLIENT)) \
	$(addprefix src/utils/, $(__SRC_UTILS)) \

__SRC_SRC := server.c \
	exit.c \
	handle_clients_actions.c \
	handle_commands.c \
	read_buffer.c \
	select_wrapper.c \

__SRC_COMMANDS := commands.c \
	unknown_command.c \
	auth.c \
	utils.c \

__SRC_AI := forward.c \
	right.c \
	left.c \
	look.c \
	inventory.c \
	connect_nbr.c \
	fork.c \
	eject.c \
	take.c \
	set.c \
	incantation.c \

__SRC_GRAPHICAL := msz.c \
	bct.c \
	mct.c \
	tna.c \
	ppo.c \
	plv.c \
	pin.c \
	sgt.c \
	sst.c \
	pnw.c \
	ebo.c \

__SRC_GAME := \
	create_map.c \
	init_map.c \
	manage_entities.c \
	query_map.c \
	player_pick_up.c \
	player_death.c \

__SRC_ARGS := \
	params.c \
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

__SRC_UTILS := queue_buffer.c \
	time.c \


# =============================================================================
# Unit tests sources
# =============================================================================

__TEST_PATH := ../tests/server/src/

__TEST_SRC	= \
	$(__SRC) \
	$(__TEST_PATH)../test_global_utils.c \
	$(addprefix $(__TEST_PATH)test_, $(__SRC_ROOT_TEST)) \
	$(addprefix $(__TEST_PATH)utils/test_, $(__SRC_UTILS_TEST)) \
	$(addprefix $(__TEST_PATH)commands/test_, $(__SRC_COMMANDS_TEST)) \
	$(addprefix $(__TEST_PATH)commands/ai/test_, $(__SRC_AI_TEST)) \
	$(addprefix $(__TEST_PATH)commands/graphical/test_, $(__SRC_GFX_TEST)) \

__SRC_ROOT_TEST := utils.c \
	client.c

__SRC_COMMANDS_TEST := auth.c \

__SRC_AI_TEST	:=	\
	connect_nbr.c \
	direction.c \
	eject.c \
	fork.c \
	forward.c \
	inventory.c \
	look.c \
	take.c \
	set.c \
	incantation.c \

__SRC_GFX_TEST := msz.c \
	bct.c \
	mct.c \
	tna.c \
	ppo.c \
	plv.c \
	pin.c \
	sgt.c \
	sst.c \
	pnw.c \

__SRC_UTILS_TEST := get_map.c \

# =============================================================================
# Functionnal tests sources
# =============================================================================


__TESTER_SRC := tests/tester.cpp \
	tests/Test.cpp


# =============================================================================
# Compilation flags
# =============================================================================


__CC = gcc
__CFLAGS += -Wall -Wextra -Werror -Wpedantic
__CFLAGS += -I./include -L. -lmy -lnetwork -luuid
__TEST_FLAGS = $(__CFLAGS) --coverage -lcriterion \
	-I../tests/server -I../tests -I../tests/server/src

%.o: %.c
	@$(__CC) -c -o $@ $< $(__CFLAGS)


# =============================================================================
# Objects
# =============================================================================


__OBJ = $(__ASRC:.c=.o)
__TESTER_OBJ = $(__TESTER_SRC:.cpp=.o)

%.o: %.cpp
	@g++ -c -o $@ $< -std=c++20


# =============================================================================
# Basic rules
# =============================================================================


all: $(__LIBMY) $(__LIBNETWORK) $(__NAME)

$(__NAME): $(__OBJ)
	@$(__CC) -o $(__NAME) $(__OBJ) $(__CFLAGS)
	@echo -ne "\n${__INFO} Server compiled successfully.${__NC}\n"

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
	@$(CC) -o $(__TEST) $(__TEST_SRC) $(__TEST_FLAGS)
	@./$(__TEST)

tests_clean:
	@make fclean -i -C ./lib -s
	@rm -f $(__NAME)
	@rm -f $(__OBJ)
	@rm -f $(__TESTER_NAME)
	@rm -f $(__TESTER_OBJ)
	@rm -f $(__TEST)
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
