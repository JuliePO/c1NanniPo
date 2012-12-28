# $(BIN) est la nom du binaire genere
BIN = ./bin/imagimp
# FLAG
CFLAGS = -Wall -g
LDFLAGS= -lglut -lGL -lGLU -lm -lglimagimp -Llib/libglimagimp.so
# INCLUDES
INC = ./lib/include/
# INCLUDES
LIBDIR = ./lib
# Compilateur
CC = gcc
# SRC
DIR_SRC = src
POINTC = $(wildcard *.c)
SRC = $(wildcard $(DIR_SRC)/*.c)
# OBJET
DIR_OBJ = obj
#OBJ= $(SRC:$(DIR_SRC)/.c=$(DIR_OBJ)/.o)
OBJ = $(DIR_OBJ)/calque.o $(DIR_OBJ)/image.o $(DIR_OBJ)/main.o
OBJ_MAIN = $(DIR_SRC)/main.c lib/include/interface.h lib/include/outils.h $(OBJ)


all: $(BIN)

$(BIN):$(OBJ)
	@$(CC) -I$(INC) -o $@ $^ -L$(LIBDIR) $(LDFLAGS)
	@echo "Compilation OK"

$(DIR_OBJ)/main.o: $(OBJ_MAIN)
	@echo "**** main.o ****"
	$(CC) -I$(INC) $(CFLAGS) -c $< -o $@ -L$(LIBDIR) $(LDFLAGS)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	@echo "**** $@ ****"
	$(CC) -I$(INC) -o $@ -c $< $(CFLAGS)
	@echo "Creation $@ OK"
	@echo "****************"

clean:
	rm -rf $(DIR_OBJ)/*.o
	@echo "File .o are all removed" 	

mrproper: clean
	rm -rf $(BIN)
	@echo "File .o and .exe are all removed"
	
