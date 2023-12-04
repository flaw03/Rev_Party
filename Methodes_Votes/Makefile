# Compilateur
CC=gcc

# Options de compilation
CFLAGS=-Wall

# Répertoire de destination pour les fichiers objet (.o)
OBJ_DIR=obj

# Répertoire de destination pour les exécutables
BIN_DIR=bin

# Répertoire de destination pour la documentation
DOC_DIR=documentation

# Liste des fichiers source (.c)
SRC=Utiles.c lecture.c jugement.c Uninominales.c main.c

# Nom de l'exécutable
EXEC=main

# Fichiers objets (.o) dérivés des fichiers source
OBJ= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

# Règle par défaut pour tout compiler
all: directories $(BIN_DIR)/$(EXEC)

# Création des répertoires
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Règle pour créer l'exécutable
$(BIN_DIR)/$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Règle générique pour compiler les fichiers source en fichiers objets
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean doc

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(DOC_DIR)

# Règle pour générer la documentation avec Doxygen
doc:
	@doxygen Doxyfile

