NAME_PROGRAM = indice
CC = gcc
FLAGS = -lm -pedantic -Wall -g
C_FILES = $(wildcard *.c)
O_FILES = $(patsubst %.c, %.o, $(C_FILES))

all: clean $(O_FILES) create_executable

main.o: main.c
	@ $(CC) -c $< $(FLAGS)
	

%.o: %.c %.h

	@ $(CC) -c -g $< $(FLAGS)

create_executable: 
	@ $(CC) -g -o $(NAME_PROGRAM) $(O_FILES) -lm

run: 
	@ ./$(NAME_PROGRAM)

test: clean all run

valgrind: 
	@ valgrind ./$(NAME_PROGRAM)

clean: 
	@ rm -rf $(NAME_PROGRAM) $(O_FILES)