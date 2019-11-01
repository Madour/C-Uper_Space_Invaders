CC = gcc
CC_FLAGS = -Wall

C_FILES = window.c entities.c alien.c sprites.c levels.c alphabet.c main.c boss.c
O_FILES = $(C_FILES:.c=.o)
H_FILES = $(C_FILES:.c=.h)

LIBS_NAME = -lX11 -lSDL2_mixer
LIBS_PATH = 

PRGM = space
BIN_DIR = ..

all : build

build: $(PRGM)
	mv $(PRGM) $(BIN_DIR)

$(PRGM): $(O_FILES)
	$(CC) $(CC_FLAGS) -o $(PRGM) $(O_FILES) $(LIBS_NAME) $(LIB_PATH)

%.o: %.c %.h
	$(CC) $(CC_FLAGS) -c $<

.depend:
	$(CC) -MM $(C_FILES) > $@

-include .depend

clean:
	rm -f .depend
	rm -f $(O_FILES)
	rm -f $(BIN_DIR)/$(PRGM)

.PHONY: clean
