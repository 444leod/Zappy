##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

NAME_LIB = libmy.a
NAME_NETWORK_LIB = libnetwork.a

SRC_MY_LIB = 	my/debug_print.c \
	my/escaped_string.c \
	my/garbage_collector.c \
	my/garbage_llist.c \
	my/get_current_dir.c \
	my/my_error.c \
	my/my_snprintf.c \
	my/my_strdup.c \
	my/replace_char.c \
	my/str_to_word_array.c \
	my/supercat.c \
	my/tablen.c \
	my/linked_list.c \
	my/is_number.c \
	my/is_alphanum.c \

SRC_NETWORK_LIB = 	network/accept_socket.c \
	network/bind_socket.c \
	network/connect_to_server.c \
	network/get_port.c \
	network/get_socket.c \
	network/listen_socket.c \
	network/build_packet.c \
	network/send_packet.c \
	network/packet_queue.c \

OBJ_MY_LIB = $(SRC_MY_LIB:.c=.o)
OBJ_NETWORK_LIB = $(SRC_NETWORK_LIB:.c=.o)

CFLAGS = -Wall -Wextra -Werror -Wpedantic -I../include

all: $(NAME_LIB) $(NAME_NETWORK_LIB)

$(NAME_LIB): $(OBJ_MY_LIB)
	ar rc $(NAME_LIB) $(OBJ_MY_LIB)
	cp $(NAME_LIB) ../

$(NAME_NETWORK_LIB): $(OBJ_NETWORK_LIB)
	ar rc $(NAME_NETWORK_LIB) $(OBJ_NETWORK_LIB)
	cp $(NAME_NETWORK_LIB) ../

clean:
	rm -f $(OBJ_MY_LIB) $(OBJ_NETWORK_LIB)

fclean: clean
	rm -f $(NAME_LIB) $(NAME_NETWORK_LIB)
	rm -f ../$(NAME_LIB) ../$(NAME_NETWORK_LIB)

re: fclean all

debug: all

dev: all


.PHONY: all clean fclean re
