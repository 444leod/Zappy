##
## EPITECH PROJECT, 2024
## myteams_server
## File description:
## Makefile
##

NAME = myteams_server

SRC = main.c \
	$(addprefix src/, $(SRC_SRC)) \
	$(addprefix src/network/, $(NETWORK_SRC)) \
	$(addprefix src/network/client_linked_list/, $(CLIENT_LLIST_SRC)) \
	$(addprefix src/network/user_linked_list/, $(USER_LLIST_SRC)) \
	$(addprefix src/commands/, $(COMMANDS_SRC)) \

SRC_SRC = server.c \
	check_args.c \
	handle_clients.c \
	handle_commands.c \
	exit.c \
	context.c \

COMMANDS_SRC = commands.c \
	create.c \
	info.c \
	list.c \
	login.c \
	logout.c \
	messages.c \
	send.c \
	subscribe.c \
	subscribed.c \
	unsubscribe.c \
	use.c \
	user.c \
	users.c \
	unknown_command.c \

NETWORK_SRC = reply_code.c \
	special_print.c \
	global_packet_send.c \
	threads/create_thread.c \
	threads/get_threads.c \
	threads/get_thread.c \
	threads/init_threads.c \
	threads/dump_threads.c \
	teams/create_team.c \
	teams/get_teams.c \
	teams/get_team.c \
	teams/init_teams.c \
	teams/dump_teams.c \
	replies/create_reply.c \
	replies/get_replies.c \
	replies/get_reply.c \
	replies/init_replies.c \
	replies/dump_replies.c \
	channels/create_channel.c \
	channels/get_channels.c \
	channels/get_channel.c \
	channels/init_channels.c \
	channels/dump_channels.c \
	messages/create_message.c \
	messages/get_messages.c \
	messages/get_message.c \
	messages/init_messages.c \
	messages/dump_messages.c \

CLIENT_LLIST_SRC = add_client.c \
	create_client.c \
	remove_client.c \
	get_clients.c \
	clear_clients.c \

USER_LLIST_SRC = add_user.c \
	dump_users.c \
	get_users.c \
	init_users.c \
	is_user.c \

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Wpedantic \
	-I./include -I../include \
	-luuid -L ../libs/myteams/ -lmyteams -L ../ -lmy -lnetwork \
	-I ../libs/myteams

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run:
	exit 0

run: all

debug:
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) -g

dev:
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) -g -DDEV_MODE

.PHONY: all clean fclean re
.SILENT: run
