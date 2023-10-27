# Répertoire de destination pour les fichiers objet (.o)
OBJ_DIR=obj

# Répertoire de destination pour les exécutables
BIN_DIR=bin

# Nom de l'exécutable
EXEC=verify_my_vote

# Compilateur
CC=gcc

# Options de compilation
CFLAGS=-std=c99 -Werror -Wextra -Wall -pedantic 
# Options de l'édition de liens
LDFLAGS=-lm

# Liste des fichiers source (.c)
SRC= $(wildcard *.c)

# Liste des fichiers objets (.o)
OBJ= $(SRC:%.c=$(OBJ_DIR)/%.o) $(SHA256_SRC:%.c=$(OBJ_DIR)/%.o)

# Règle par défaut pour tout compiler
all: 
ifeq ($(DEBUG),yes)
	CFLAGS += -DDEBUG
	@echo "Generating in debug mode"
else
	@echo "Generating in release mode"
endif
	@$(MAKE) $(EXEC)

# Règle pour créer l'exécutable
$(EXEC): $(OBJ)
	@$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

# Règle générique pour compiler les fichiers source en fichiers objets
$(OBJ_DIR)/%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

# Règle pour créer l'exécutable verify_my_vote
$(BIN_DIR)/verify_my_vote: $(OBJ_DIR)/verify_my_vote.o
	@$(CC) -o $@ $< Sha256/sha256.c Sha256/sha256_utils.c  6 $(LDFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf $(OBJ_DIR)/*.o
	@rm -rf $(BIN_DIR)/$(EXEC) documentation/TP2

doc: lecture_csv.h verify_my_vote.h 
	@doxygen documentation/TP2
