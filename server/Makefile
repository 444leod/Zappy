##
## EPITECH PROJECT, 2024
## myTeams
## File description:
## Makefile
##

GREEN=\033[0;32m
NC=\033[0m

INFO = ${GREEN}[INFO]${NC}

all:
	make -C ./common -s
	make -C ./server -s
	@mv ./server/myteams_server ./myteams_server
	make -C ./client -s
	@mv ./client/myteams_cli ./myteams_cli
	@echo -ne "\n${INFO} Server and client compiled successfully.${NC}\n"

clean:
	make clean -C ./common -s
	make clean -C ./server -s
	make clean -C ./client -s
	@echo -ne "\n${INFO} Server and client cleaned.${NC}\n"

fclean: clean
	make fclean -C ./common -s
	make fclean -C ./server -s
	make fclean -C ./client -s
	rm -f myteams_server
	rm -f myteams_cli
	@echo -ne "\n${INFO} Server and client cleaned.${NC}\n"

re: fclean all

tests_run:
	make tests_run -C ./server -s
	make tests_run -C ./client -s
	@echo -ne "\n${INFO} Tests run.${NC}\n"

debug:
	make debug -C ./common -s
	make debug -C ./server -s
	@mv ./server/myteams_server ./myteams_server
	make debug -C ./client -s
	@mv ./client/myteams_cli ./myteams_cli
	@echo -ne "\n${INFO} Debug mode compiled successfully.${NC}\n"

dev:
	make dev -C ./common -s
	make dev -C ./server -s
	@mv ./server/myteams_server ./myteams_server
	make dev -C ./client -s
	@mv ./client/myteams_cli ./myteams_cli
	@echo -ne "\n${INFO} Dev mode compiled successfully.${NC}\n"

init: install-hooks install-mango

install-hooks:
	@cp .githooks/commit-msg .git/hooks/commit-msg
	@chmod +x .git/hooks/commit-msg
	@echo "Hooks installed."

install-mango:
	@chmod +x ./init/install-mango.sh
	@./init/install-mango.sh

.PHONY: all clean fclean re
.SILENT: run
