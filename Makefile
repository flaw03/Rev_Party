# Specific part of the Makefile
EXEC=verify
# Begin generic part of the Makefile

CC=gcc
CFLAGS=-std=c99 -Werror -Wextra -Wall -pedantic
LDFLAGS=-lm

SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: 
ifeq ($(DEBUG),yes)
	@echo "Generating in debug mode"
else
	@echo "Generating in release mode"
endif
	@$(MAKE) $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC) documentation/TP2

doc: lecture_csv.h verify_my_vote.h 
	@doxygen documentation/TP2
# End generic part of the makefile
# List of target dependencies
#verify_my_vote.o: verify_my_vote.h lecture_csv.h 