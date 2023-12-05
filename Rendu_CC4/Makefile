# Répertoire de destination pour les fichiers objet (.o)
OBJ_DIR=obj

# Répertoire de destination pour les exécutables
BIN_DIR=bin

# Nom de l'exécutable
EXEC=scrutin

# Compilateur
CC=gcc

# Options de compilation
CFLAGS=-std=c99 -Wextra -Wall -pedantic -Werror -Wunused-parameter -D_POSIX_C_SOURCE=200809L

# Options de l'édition de liens
LDFLAGS=-lm

ifeq ($(DEBUG),yes)
	CFLAGS += -g
	LDFLAGS +=
else
	CFLAGS += -O3 -DNDEBUG
	LDFLAGS +=
endif

# Liste des fichiers source (.c)
SRC= $(wildcard *.c)

# Liste des fichiers objets (.o)
OBJ= $(SRC:%.c=$(OBJ_DIR)/%.o)

# Règle par défaut pour tout compiler
all: $(EXEC)

ifeq ($(DEBUG),yes)
	@echo "Generating in debug mode"
else
	@echo "Generating in release mode"
endif

# Règle pour créer l'exécutable
$(EXEC): $(OBJ)
	@mkdir -p $(BIN_DIR)
	@$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

# Règle générique pour compiler les fichiers source en fichiers objets
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean doc deliver

mrproper: clean
	@rm -rf $(EXEC) documentation/html


clean:
	@rm -rf $(OBJ_DIR)/*.o

doc: fichiers.h/set.h fichiers.h/condorcet.h fichiers.h/jugement.h fichiers.h/lecture.h fichiers.h/list.h fichiers.h/Uninominales.h fichiers.h/Utiles.h fichiers.h/utils_tab.h
	@doxygen documentation/DOXYFILE


DELIVER_FMT=$(shell date "+%d-%m-%y_%Hh%Mm%Ss")

deliver:
	@zip -r $(DELIVER_FMT).zip .


