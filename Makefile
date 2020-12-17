# ====================
# npc-game
# GNU/Linux
# ====================

# Constantes:
# ====================
CC = gcc
CFLAGS = -W -Wall -ansi -std=c99 -g
LIBS = 
LDFLAGS = $(sdl2-config --cflags --libs)
INCLUDES = -lSDL2 -lSDL2_ttf -lSDL2_image -lm
DIR_SRC = src
DIR_RES = res
DIR_OUT = out
SRC = $(wildcard $(DIR_SRC)/*.c)
OBJ = $(SRC:$(DIR_SRC)/%.c=$(DIR_OUT)/%.o)
EXEC = npc-game

# Commandes:
# ====================

# Variables spéciales:
# $@	Nom de la cible
# $<	Nom de la première dépendance
# $^	Liste de dépendances
# $?	Liste de dépendances plus récentes que la cible
# $*	Nom du fichier sans l'extension

all: build $(EXEC)

build:
	mkdir -p $(DIR_OUT)

$(DIR_OUT)/%.o: $(DIR_SRC)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDES)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(INCLUDES)

clean:
	rm -rf $(DIR_OUT)

mrproper: clean
	rm -f $(EXEC)