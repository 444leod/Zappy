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

__NAME = zappy

all: $(__NAME)

check_init: .init_done

.init_done:
	@echo "Debug: $(__BOLD)${__GREEN}${FORCE_MAKE}"
	@if [ -z "${FORCE_MAKE}" ]; then \
		if [ $(check_init) = "false" ]; then \
			echo -ne "${__RED}Repository is not initialized. "; \
			echo -e "Please run $(__BOLD)'make init'${__NC}$(__RED).${__NC}"; \
			exit 1; \
		else \
			touch .init_done; \
		fi \
	else \
		echo "${__GREEN}Forced Makefile rule."; \
	fi

$(__NAME): .init_done
	@make -s -C server
	@make -s -C gui
	@make -s -C ai
	@mv server/zappy_server .
	@mv gui/zappy_gui .
	@mv ai/zappy_ai .
	@echo -ne "${__GREEN}$(__BOLD)Compilation$(__NC)"
	@echo -e "${__GREEN}completed successfully.${__NC}"
clean:
	@make clean -s -C server
	@make clean -s -C gui
	@make clean -s -C ai
	@rm -f zappy_server
	@rm -f zappy_gui
	@rm -f zappy_ai
	@echo -ne "${__GREEN}$(__BOLD)Clean$(__NC)"
	@echo -e "${__GREEN}completed successfully.${__NC}"

fclean: clean
	@make fclean -s -C server
	@make fclean -s -C gui
	@make fclean -s -C ai
	@echo -ne "${__GREEN}$(__BOLD)Fclean$(__NC)"
	@echo -e "${__GREEN}completed successfully.${__NC}"

re: fclean all


tests_run:	.init_done
	@make tests_run -s -C server

tests_clean:
	@make tests_clean -s -C server

tests: tests_run tests_clean

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
