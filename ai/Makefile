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

__ENTRY_POINT = ./bot.py
__SRC = 		./ai_src/commands.py\
				./ai_src/config.py \
				./ai_src/connection_handler.py \
				./ai_src/data.py \



all: $(__NAME)

$(__NAME):
	@cp $(__ENTRY_POINT) zappy_ai
	@mkdir -p ../ai_src
	@cp $(__SRC) ../ai_src
	@chmod +x zappy_ai
	@echo -ne "${__GREEN}$(__BOLD)Compilation of $(__NAME)$(__NC)"
	@echo -e "${__GREEN}completed successfully.${__NC}"
clean:
	@echo -e "${__GREEN}Nothing to clean in Python project${__NC}"
	@echo -ne "${__GREEN}$(__BOLD)Clean of $(__NAME)$(__NC)"
	@echo -e "${__GREEN}completed successfully.${__NC}"

fclean: clean
	@rm -f $(__NAME)
	@rm -rf ../ai_src
	@echo -ne "${__GREEN}$(__BOLD)Fclean of $(__NAME)$(__NC)"
	@echo -e "${__GREEN}completed successfully.${__NC}"

re: fclean all

tests_run: all

run: all

.PHONY: all clean fclean re
.SILENT: run
