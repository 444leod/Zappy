##
## EPITECH PROJECT, 2024
## PROJECT_NAME
## File description:
## Makefile
##

__RED=\033[0;31m
__GREEN=\033[0;32m
__BOLD=\033[1m
__NC=\033[0m
__NC=\033[0m

DIR = $(shell pwd)
LIB_DIR = $(DIR)/lib

__NAME = zappy_gui

__SRC = src/ArgumentChecking.cpp \
  	$(addprefix ./src/Core/, $(__SRC_CORE)) \
	$(addprefix ./src/network/, $(__SRC_NETWORK)) \
  	$(addprefix ./src/GameData/, $(__SRC_GAME_DATA)) \
  	$(addprefix ./src/Handler/Command/, $(__SRC_GAME_DATA_MANAGER)) \
  	$(addprefix ./src/Handler/Command/CommandProtocol/, $(__SRC_CMD_HANDLE)) \
  	$(addprefix ./src/GameDisplay/, $(__SRC_GAME_DISPLAY)) \

__SRC_CORE := Core.cpp \
	GraphicalLibraryLoader.cpp \

__SRC_GAME_DISPLAY := GameDisplay.cpp \

__SRC_NETWORK := Client.cpp \

__SRC_GAME_DATA := GameData.cpp \
	Tiles/Map.cpp \
	Tiles/TileContent.cpp \

__SRC_GAME_DATA_MANAGER := GameDataManager.cpp \

__SRC_CMD_HANDLE := Map/Bct.cpp \
	Map/Msz.cpp \
	Map/Mct.cpp \
	Entities/Tna.cpp \
	Entities/Pnw.cpp \
	Entities/Ppo.cpp \
	Entities/Plv.cpp \
	Entities/Pin.cpp \
	Action/Pic.cpp \
	Action/Pie.cpp \
	Action/Pdr.cpp \
	Action/Pgt.cpp \
	Action/Pex.cpp \
	Action/Pbc.cpp \
	Action/Enw.cpp \
	Action/Pfk.cpp \
	Server/Smg.cpp \
	Server/Suc.cpp \
	Server/Sbp.cpp \
	Server/Ebo.cpp \
	Status/Sst.cpp \
	Status/Pdi.cpp \
	Status/Seg.cpp \
	Status/Sgt.cpp \
	Status/Edi.cpp \

%.o: %.cpp
	@$(__CC) -c -o $@ $< $(__CXXFLAGS)
%.o: %.cpp
	@$(__CC) -c -o $@ $< $(__CXXFLAGS)

__OBJ = $(__SRC:.cpp=.o)
__OBJ = $(__SRC:.cpp=.o)

__CC = g++
__CC = g++

__CXXFLAGS += -Wall -Wextra -Werror -Wpedantic -std=c++20
__CXXFLAGS += -lsfml-network -lsfml-system
__CXXFLAGS += -I./include -I./src/network -I./include/GameData
__CXXFLAGS += -I./include/Handler/Command/CommandProtocol
__CXXFLAGS += -I./include/Handler/Command/CommandProtocol/Map
__CXXFLAGS += -I./include/Handler/Command/CommandProtocol/Entities
__CXXFLAGS += -I./include/Handler/Command/CommandProtocol/Action
__CXXFLAGS += -I./include/Handler/Command/CommandProtocol/Server
__CXXFLAGS += -I./include/Handler/Command/CommandProtocol/Status
__CXXFLAGS += -I./include/Handler/Command/ -I./include/Handler/
__CXXFLAGS += -I./include/Graphics

all: $(__NAME)

$(__NAME): $(__OBJ)
	make -s -C src/Graphics/SFML2d 		 LIB_DIR=$(LIB_DIR)
	@$(__CC) -o $(__NAME) $(__OBJ) $(__CXXFLAGS)
	@$(__CC) -o $(__NAME) $(__OBJ) $(__CXXFLAGS)
	@echo -ne "${__GREEN}$(__BOLD)Compilation of $(__NAME)$(__NC)"
	@echo -e " ${__GREEN}completed successfully.${__NC}"
	@echo -e " ${__GREEN}completed successfully.${__NC}"
clean:
	make -s -C src/Graphics/SFML2d clean LIB_DIR=$(LIB_DIR)
	@rm -f $(__OBJ)
	@echo -ne "${__GREEN}$(__BOLD)Clean of $(__NAME)$(__NC)"
	@echo -e " ${__GREEN}completed successfully.${__NC}"
	@echo -e " ${__GREEN}completed successfully.${__NC}"

fclean: clean
	make -s -C src/Graphics/SFML2d fclean LIB_DIR=$(LIB_DIR)
	@rm -f $(__NAME)
	@echo -ne "${__GREEN}$(__BOLD)Fclean of $(__NAME)$(__NC)"
	@echo -e " ${__GREEN}completed successfully.${__NC}"
	@echo -e " ${__GREEN}completed successfully.${__NC}"

re: fclean all
