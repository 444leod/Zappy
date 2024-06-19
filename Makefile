##
## EPITECH PROJECT, 2024
## PROJECT_NAME
## File description:
## Makefile
##

__RED=\033[0;31m
__GREEN=\033[0;32m
__BLUE=\033[0;34m
__BOLD=\033[1m
__NC=\033[0m # No Color

__NAME = zappy

all: $(__NAME)

check_init: .init_done

.init_done:
	@echo "Debug: $(__BOLD)${__GREEN}${FORCE_MAKE}"
	@if [ -z "${FORCE_MAKE}" ]; then \
		if [ $(check_init) = "false" ]; then \
			printf "$(__RED)Repository is not initialized. "; \
			printf "Please run $(__BOLD)'make init'$(__NC)$(__RED).$(__NC)"; \
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
	@printf "$(__GREEN)$(__BOLD)Compilation of zappy_server$(__NC)\n"
	@printf "$(__GREEN)completed successfully.$(__NC)\n"

dev: .init_done
	@make dev -s -C server
	@make -s -C gui
	@make -s -C ai
	@mv server/zappy_server .
	@mv gui/zappy_gui .
	@mv ai/zappy_ai .
	@printf "$(__BLUE)$(__BOLD)Compilating dev mode for zappy_server$(__NC)\n"
	@printf "$(__BLUE)completed successfully.$(__NC)\n"

clean:
	@make clean -s -C server
	@make clean -s -C gui
	@make clean -s -C ai
	@rm -f zappy_server
	@rm -f zappy_gui
	@rm -f zappy_ai
	@printf "$(__GREEN)$(__BOLD)Clean$(__NC)\n"
	@printf "$(__GREEN)completed successfully.$(__NC)\n"

fclean: clean
	@make fclean -s -C server
	@make fclean -s -C gui
	@make fclean -s -C ai
	@printf "$(__GREEN)$(__BOLD)Fclean$(__NC)\n"
	@printf "$(__GREEN)completed successfully.$(__NC)\n"

re: fclean all


tests_run:	.init_done
	@printf "\n$(__BOLD)$(__GREEN)SERVER TESTS$(__NC)\n"
	@make tests_run -s -C server
	@printf "\n$(__BOLD)$(__GREEN)SERVER LIBS TESTS$(__NC)\n"
	@make tests_run -s -C server/lib

tests_clean:
	@make tests_clean -s -C server
	@make tests_clean -s -C server/lib

tests: tests_run tests_clean

unit_tests:
	@make unit_tests_run -s -C server
	@make tests_run -s -C server/lib
	@make tests_clean -s -C server
	@make tests_clean -s -C server/lib

coverage:
	@make tests_run -s -C server
	@make tests_run -s -C server/lib
	@gcovr -e tests
	@make tests_clean -s -C server
	@make tests_clean -s -C server/lib

run: all

init: install-dependancies install-hooks install-mango __update-repo-config

install-dependancies:
	@if [ $(is_jq_installed) = "false" ]; then \
		printf "${__RED}jq is not installed.\n" \
		printf "$(__BOLD)Please install jq beforehand.${__NC}\n";\
		exit 1; \
	fi

install-hooks:
	@cp .githooks/commit-msg .git/hooks/commit-msg
	@chmod +x .git/hooks/commit-msg
	@printf "${__GREEN}$(__BOLD)Hooks$(__NC)\n"
	@printf "${__GREEN}installed successfully.${__NC}\n"

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
