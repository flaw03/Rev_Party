
# Répertoire de destination pour les fichiers objet (.o)
OBJ_DIR=obj

# Répertoire de destination pour les exécutables
BIN_DIR=bin

# Nom de l'exécutable
EXEC=test

# Compilateur
CC=gcc


# Options de compilation
CFLAGS=-std=c99 -Wextra -Wall -pedantic -Werror -Wunused-parameter
# Options de l'édition de liens
LDFLAGS=-lm

# Liste des fichiers source (.c)
SRC= $(wildcard *.c)

# Liste des fichiers objets (.o)
OBJ= $(SRC:%.c=$(OBJ_DIR)/%.o) $(SHA256_SRC:%.c=$(OBJ_DIR)/%.o)

# Règle par défaut pour tout compiler
all: 
ifeq ($(DEBUG),yes)
	@echo "Generating in debug mode"
else
	@echo "Generating in release mode"
endif
	@$(MAKE) $(EXEC)

# Règle pour créer l'exécutable
$(EXEC): $(OBJ)
	@mkdir -p $(BIN_DIR)
	@$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

# Règle générique pour compiler les fichiers source en fichiers objets
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -o $@ -c $< $(CFLAGS)


.PHONY: clean mrproper

clean:
	@rm -rf $(OBJ_DIR)/*.o
	@rm -rf $(BIN_DIR)/$(EXEC) documentation/TP2
