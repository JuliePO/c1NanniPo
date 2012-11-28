# $(BIN) est la nom du binaire genere
BIN = ./obj/imagimp
# FLAG
FLAGS = -Wall -g
# INCLUDES
INC = ./lib/include
# INCLUDES
LIBDIR = ./lib
# Librairies
LIBS =  -lglimagimp -lglut -lGL -lGLU
# Compilateur
CC = gcc
# Compilateur
SRC = ./src/main.c

all:
	@echo "**** TEST ****"
	$(CC) -o $(BIN) $(FLAGS) -I$(INC) $(SRC) -L$(LIBDIR) $(LIBS) 

clean:
	rm -f $(BIN)