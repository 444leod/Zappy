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
__LIBMY = libmy.a
__LIBNETWORK = libnetwork.a

__ASRC = $(__SRC) \
	main.c

__SRC	=	$(addprefix src/, $(__SRC_SRC)) \
	$(addprefix src/commands/, $(__SRC_COMMANDS)) \
	$(addprefix src/network/, $(__SRC_NETWORK)) \
	$(addprefix src/network/client/, $(__SRC_CLIENT)) \

__TEST_SRC	=	$(__SRC) \
	$(addprefix ../tests/server/, $(__SRC_ROOT_TEST))

__SRC_SRC := server.c \
	exit.c \
	check_args.c \
	handle_clients.c \
	handle_commands.c

__SRC_COMMANDS := commands.c \
	unknown_command.c \
	msz.c

__SRC_NETWORK := global_packet_send.c \
	send_packets.c \
	special_print.c \

__SRC_CLIENT := add_client.c \
	clear_clients.c \
	create_client.c \
	get_clients.c \
	remove_client.c \

# Add server tests sources here.
__SRC_ROOT_TEST := sample.c \
	client.c

%.o: %.c
	@$(__CC) -c -o $@ $< $(__CFLAGS)

__OBJ = $(__ASRC:.c=.o)

__TEST_OBJ = $(__TEST_SRC:.c=.o)

__CC = gcc
__CFLAGS += -Wall -Wextra -Werror -Wpedantic -I./include -L. -lmy -lnetwork
__TEST_FLAGS = $(__CFLAGS) --coverage -lcriterion

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

tests_run: $(__LIBMY) $(__LIBNETWORK)
	@gcc -o $(__TEST) $(__TEST_SRC) $(__TEST_FLAGS)
	@
	@./$(__TEST)

tests_clean:
	@make fclean -C ./lib -s
	@rm -f $(__TEST_OBJ)
	@rm -f $(__TEST)
	@find . -name "*.gcda" -delete
	@find . -name "*.gcno" -delete

coverage: tests_run
	@gcovr .

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
