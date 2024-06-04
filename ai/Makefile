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

__SRC = ./src/bot.py

all: $(__NAME)

$(__NAME):
	@cp $(__SRC) zappy_ai
	@chmod +x zappy_ai
	@echo -ne "${__GREEN}$(__BOLD)Compilation of $(__NAME)$(__NC)"
	@echo -e "${__GREEN}completed successfully.${__NC}"
clean:
	@echo -e "${__GREEN}Nothing to clean in Python project${__NC}"
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
