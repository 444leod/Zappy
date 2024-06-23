##
## EPITECH PROJECT, 2024
## PROJECT_NAME
## File description:
## Makefile
##

__GREEN=\033[0;32m
__NC=\033[0m
__INFO = ${__GREEN}[INFO]${__NC}

__NAME = zappy_ai

__ENTRY_POINT = ./bot.py
__SRC = 		./ai_src/commands.py\
				./ai_src/config.py \
				./ai_src/connection_handler.py \
				./ai_src/data.py \
				./ai_src/behaviors.py \
				./ai_src/utils.py

all: $(__NAME)

$(__NAME):
	@cp $(__ENTRY_POINT) zappy_ai
	@mkdir -p ../ai_src
	@cp $(__SRC) ../ai_src
	@chmod +x zappy_ai
	@echo -ne "\n${__INFO} AI compiled successfully.${__NC}\n"
clean:
	@echo -ne "\n${__INFO} AI cleaned.${__NC}\n"

fclean: clean
	@rm -f $(__NAME)
	@rm -rf ../ai_src
	@echo -ne "\n${__INFO} AI fully cleaned.${__NC}\n"

re: fclean all

tests_run: all

run: all

.PHONY: all clean fclean re
.SILENT: run
