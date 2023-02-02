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
	@ ./$(NAME_PROGRAM) /home/felipecarpes/TrabDupla/trab2/small/medium-large/train.txt indice.bin

test: clean all run

val: 
	@ valgrind --leak-check=full -s ./$(NAME_PROGRAM) /home/felipecarpes/TrabDupla/trab2/small/medium-small/train.txt > output.txt

clean: 
	@ rm -rf $(NAME_PROGRAM) $(O_FILES)