##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

DISPLAY_NAME = zappy_sfml2d.so
NAME = $(LIB_DIR)/$(DISPLAY_NAME)

CPPFLAGS = -fPIC -iquote -std=c++20 -Wall -Wextra -Werror
CPPFLAGS += -I../../../include/Graphics
SHARED_FLAGS = -shared
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC = ./SFML2d.cpp

all: $(NAME)

clean:

fclean: clean
	@rm -f $(NAME)

re: fclean all

$(LIB_DIR):
	@mkdir -p $(LIB_DIR)

$(NAME): $(SRC) | $(LIB_DIR)
	@$(CC) $(SHARED_FLAGS) $(SRC) -o $(NAME) $(CPPFLAGS) $(SFML_FLAGS)
	@echo "[GUI] $(DISPLAY_NAME) generated"
