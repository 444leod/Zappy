##
## EPITECH PROJECT, 2024
## myTeams
## File description:
## Makefile
##

NAME_LIB = libmy.a
NAME_NETWORK_LIB = libnetwork.a

SRC_LIB = 	./lib/debug_print.c \
	./lib/escaped_string.c \
	./lib/garbage_collector.c \
	./lib/garbage_llist.c \
	./lib/get_current_dir.c \
	./lib/uuid.c \
	./lib/magic_number.c \
	./lib/my_error.c \
	./lib/my_snprintf.c \
	./lib/my_strdup.c \
	./lib/replace_char.c \
	./lib/str_to_word_array.c \
	./lib/supercat.c \
	./lib/tablen.c \
	./lib/quote_splitter.c \
	./lib/linked_list.c \

SRC_NETWORK_LIB = 	./network/accept_socket.c \
	./network/bind_socket.c \
	./network/connect_to_server.c \
	./network/get_port.c \
	./network/get_socket.c \
	./network/listen_socket.c \
	./network/build_packet.c \
	./network/build_special_packet.c \
	./network/read_packet.c \
	./network/read_special_packet.c \
	./network/send_packet.c \
	./network/packet_queue.c \

CC = gcc

CFLAGS = -I../include -Wall -Wextra -Werror -Wpedantic -luuid \
	-I ../libs/myteams

OBJ_LIB = $(SRC_LIB:.c=.o)
OBJ_NETWORK_LIB = $(SRC_NETWORK_LIB:.c=.o)

all: $(NAME_LIB) $(NAME_NETWORK_LIB)

$(NAME_LIB): $(OBJ_LIB)
	ar rc $(NAME_LIB) $(OBJ_LIB)
	cp $(NAME_LIB) ../

$(NAME_NETWORK_LIB): $(OBJ_NETWORK_LIB)
	ar rc $(NAME_NETWORK_LIB) $(OBJ_NETWORK_LIB)
	cp $(NAME_NETWORK_LIB) ../

clean:
	rm -f $(OBJ_LIB) $(OBJ_NETWORK_LIB)

fclean: clean
	rm -f $(NAME_LIB) $(NAME_NETWORK_LIB)
	rm -f ../$(NAME_LIB) ../$(NAME_NETWORK_LIB)

re: fclean all

debug: all

dev: all


.PHONY: all clean fclean re
