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

__NAME = EXECUTABLE_NAME

__SRC = ./src/main.c

%.o: %.c
	@$(__CC) -c -o $@ $< $(__CFLAGS)

__OBJ = $(__SRC:.c=.o)

__CC = gcc

__CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: $(__NAME)

check_init: .init_done

.init_done:
	@if [ $(check_init) = "false" ]; then \
		echo -ne "${__RED}Repository is not initialized. "; \
		echo -e "Please run $(__BOLD)'make init'${__NC}$(__RED).${__NC}"; \
		exit 1; \
	else \
		touch .init_done; \
	fi

$(__NAME): .init_done $(__OBJ)
	@$(__CC) -o $(__NAME) $(__OBJ) $(__CFLAGS)
	@echo -ne "${__GREEN}$(__BOLD)Compilation$(__NC)"
	@echo -e "${__GREEN}completed successfully.${__NC}"
clean:
	@rm -f $(__OBJ)
	@echo -ne "${__GREEN}$(__BOLD)Clean$(__NC)"
	@echo -e "${__GREEN}completed successfully.${__NC}"

fclean: clean
	@rm -f $(__NAME)
	@echo -ne "${__GREEN}$(__BOLD)Fclean$(__NC)"
	@echo -e "${__GREEN}completed successfully.${__NC}"

re: fclean all

tests_run: all

run: all

init: install-dependancies install-hooks install-mango __update-repo-config

install-dependancies:
	@if [ $(is_jq_installed) = "false" ]; then \
		echo -ne "${__RED}jq is not installed." \
		echo "$(__BOLD)Please install jq before running this command.${__NC}";\
		exit 1; \
	fi

install-hooks:
	@cp .githooks/commit-msg .git/hooks/commit-msg
	@chmod +x .git/hooks/commit-msg
	@echo -ne "${__GREEN}$(__BOLD)Hooks$(__NC)"
	@echo -e "${__GREEN}installed successfully.${__NC}"

install-mango:
	@chmod +x ./init/install-mango.sh
	@./init/install-mango.sh

__update-repo-config:
	@chmod +x ./init/update-repository-config.sh
	@./init/update-repository-config.sh

.PHONY: all clean fclean re
.SILENT: run

define check_init
	$(shell if [ -f .repository-config.json ]; then \
		if grep -q '"repository-init": true' .repository-config.json; then \
			echo "true"; \
		else \
			echo "false"; \
		fi; \
	else \
		echo "false"; \
	fi)
endef

define is_jq_installed
	$(shell if which jq > /dev/null 2>&1; then \
		echo "true"; \
	else \
		echo "false"; \
	fi)
endef
