
# Répertoire de destination pour les fichiers objet (.o)
OBJ_DIR=obj

# Répertoire de destination pour les exécutables
BIN_DIR=bin

# Compilateur
CC=gcc

# Options de compilation
CFLAGS=-std=c99 -Wextra -Wall -pedantic -Werror -Wunused-parameter -D_POSIX_C_SOURCE=200809L

# Options de l'édition de liens
LDFLAGS=-lm




scrutin: $(OBJ_DIR)/utiles.o $(OBJ_DIR)/utils_tab.o $(OBJ_DIR)/lecture_csv.o $(OBJ_DIR)/list.o $(OBJ_DIR)/set.o  $(OBJ_DIR)/condorcet.o $(OBJ_DIR)/jugement.o $(OBJ_DIR)/uninominales.o $(OBJ_DIR)/scrutin.o 
	$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS) 2> /dev/null

verify_my_vote: $(OBJ_DIR)/utiles.o $(OBJ_DIR)/utils_tab.o $(OBJ_DIR)/lecture_csv.o $(OBJ_DIR)/sha256.o $(OBJ_DIR)/sha256_utils.o $(OBJ_DIR)/verify_my_vote.o 
	$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS) 2> /dev/null

$(OBJ_DIR)/sha256.o: sha256_module/sha256.c
	$(CC) -o $@ -c $< $(CFLAGS) 2> /dev/null

$(OBJ_DIR)/sha256_utils.o :sha256_module/sha256_utils.c sha256_module/sha256.c
	$(CC) -o $@ -c $< $(CFLAGS) 2> /dev/null

$(OBJ_DIR)/utiles.o: utility_module/utiles.c
	$(CC) -o $@ -c $< $(CFLAGS) 2> /dev/null

$(OBJ_DIR)/utils_tab.o : utility_module/utils_tab.c
	$(CC) -o $@ -c $< $(CFLAGS) 2> /dev/null

$(OBJ_DIR)/lecture_csv.o: utility_module/lecture_csv.c utility_module/utiles.h utility_module/utils_tab.h	
	$(CC) -o $@ -c $<  $(CFLAGS) 2> /dev/null

$(OBJ_DIR)/set.o: utility_module/set.c utility_module/set.h utility_module/utils_tab.h
	$(CC) -o $@ -c $< $(CFLAGS) 2> /dev/null

$(OBJ_DIR)/list.o: utility_module/list.c utility_module/list.h
	$(CC) -o $@ -c $< $(CFLAGS) 2> /dev/null

$(OBJ_DIR)/condorcet.o: scrutin_methods/condorcet.c utility_module/utils_tab.h utility_module/list.h utility_module/set.h
	$(CC) -o $@ -c $< $(CFLAGS) 2> /dev/null

$(OBJ_DIR)/jugement.o: scrutin_methods/jugement.c utility_module/utiles.h utility_module/lecture_csv.h
	$(CC) -o $@ -c $< $(CFLAGS) 2> /dev/null

$(OBJ_DIR)/uninominales.o: scrutin_methods/uninominales.c utility_module/utiles.h utility_module/lecture_csv.h
	$(CC) -o $@ -c $< $(CFLAGS) 2> /dev/null

$(OBJ_DIR)/scrutin.o: main_module/scrutin.c utility_module/utiles.h utility_module/lecture_csv.h utility_module/utils_tab.h scrutin_methods/condorcet.h scrutin_methods/jugement.h scrutin_methods/uninominales.h
	$(CC) -o $@ -c $< $(CFLAGS) 2> /dev/null

$(OBJ_DIR)/verify_my_vote.o: main_module/verify_my_vote.c utility_module/lecture_csv.h sha256_module/sha256.h sha256_module/sha256_utils.h
	$(CC) -o $@ -c $< $(CFLAGS) 2> /dev/null

$(BIN_DIR):
	mkdir -p $@

ifeq ($(DEBUG),yes)
	CFLAGS += -g
	LDFLAGS +=
else
	CFLAGS += -O3 -DNDEBUG
	LDFLAGS +=
endif


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
	@rm -rf $(BIN_DIR)/verify_my_vote
	@rm -rf $(BIN_DIR)/scrutin


doc: utility_module/set.h scrutin_methods/condorcet.h scrutin_methods/jugement.h  scrutin_methods/Uninominales.h utility_module/Utiles.h utility_module/utils_tab.h
	@doxygen documentation/DOXYFILE


DELIVER_FMT=$(shell date "+%d-%m-%y_%Hh%Mm%Ss")

deliver:
	@zip -r $(DELIVER_FMT).zip .


