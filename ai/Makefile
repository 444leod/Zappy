##
## EPITECH PROJECT, 2024
## PROJECT_NAME
## File description:
## Makefile
##

__RED=\033[0;31m
__GREEN=\033[0;32m
__BOLD=\033[1m
__NC=\033[0m # No Color

__NAME = zappy_ai

__SRC = ./src/main.c

%.o: %.c
	@$(__CC) -c -o $@ $< $(__CFLAGS)

__OBJ = $(__SRC:.c=.o)

__CC = gcc

__CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: $(__NAME)

$(__NAME): $(__OBJ)
	@$(__CC) -o $(__NAME) $(__OBJ) $(__CFLAGS)
	@echo -ne "${__GREEN}$(__BOLD)Compilation of $(__NAME)$(__NC)"
	@echo -e "${__GREEN}completed successfully.${__NC}"
clean:
	@rm -f $(__OBJ)
	@echo -ne "${__GREEN}$(__BOLD)Clean of $(__NAME)$(__NC)"
	@echo -e "${__GREEN}completed successfully.${__NC}"

fclean: clean
	@rm -f $(__NAME)
	@echo -ne "${__GREEN}$(__BOLD)Fclean of $(__NAME)$(__NC)"
	@echo -e "${__GREEN}completed successfully.${__NC}"

re: fclean all

tests_run: all

run: all

.PHONY: all clean fclean re
.SILENT: run
