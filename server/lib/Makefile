##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

NAME_LIB = libmy.a
NAME_NETWORK_LIB = libnetwork.a

TEST = lib_suite

SRC_MY_LIB = \
	my/debug_print.c \
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
	my/is_alphanum.c

MY_LIB_TESTS = \
	lib/my/test_my_exit.c \
	lib/my/test_escaped_string.c \
	lib/my/test_garbage_collector.c \
	lib/my/test_is_alphanum.c \
	lib/my/test_is_number.c \
	lib/my/test_my_snprintf.c \
	lib/my/test_linked_list.c \
	lib/my/test_my_strdup.c \
	lib/my/test_replace_char.c \
	lib/my/test_supercat.c \
	lib/my/test_tablen.c \
	lib/my/test_str_to_word_array.c \
	test_utils.c \

TEST_SRC = \
	$(SRC_MY_LIB) \
	$(addprefix ../../tests/server/, $(MY_LIB_TESTS)) \

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

CFLAGS += -Wall -Wextra -Werror -Wpedantic -I../include
TEST_FLAGS = $(CFLAGS) --coverage -lcriterion -I../../tests

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

tests_run:
	gcc -o $(TEST) $(TEST_SRC) $(TEST_FLAGS)
	@./$(TEST)

tests_clean:
	@rm -f $(TEST)
	@find . -name "*.gcda" -delete
	@find . -name "*.gcno" -delete

re: fclean all

debug: all

dev: all


.PHONY: all clean fclean re
