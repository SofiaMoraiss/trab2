NAME_PROGRAM = indice
CC = gcc
FLAGS = -lm -pedantic -Wall 
C_FILES = $(wildcard *.c)
O_FILES = $(patsubst %.c, %.o, $(C_FILES))

all: $(O_FILES) create_executable

teste:
	/home/felipecarpes/TEP1_PROG_II/artists.csv/artists.csv /home/felipecarpes/TEP1_PROG_II/tracks.csv/tracks.csv

indice.o: indice.c
	@ echo "\033[1;32m"
	@ echo "Compiling indice.c ..."
	@ $(CC) -c $< $(FLAGS)
	@ echo "\033[0m"

%.o: %.c %.h
	@ echo "\033[1;32m"
	@ echo "Compiling $< ..."
	@ $(CC) -c $< $(FLAGS)
	@ echo "\033[0m"

create_executable: 
	@ echo "\033[1;32m"
	@ echo "Creating executable..."
	@ $(CC) -g -o $(NAME_PROGRAM) $(O_FILES)  $(FLAGS)
	@ echo "\033[0m"

run: 
	@ echo "\033[1;32m"
	@ echo "Running program ..."
	@ echo "\033[0m"
	@ ./$(NAME_PROGRAM)

test: clean all run

valgrind: 
	@ echo "\033[1;32m"
	@ echo "Running valgrind ..."
	@ echo "\033[0m"
	@ valgrind ./$(NAME_PROGRAM)

diff:
	./main < /home/felipecarpes/exerciciosREVISAO/MONITORIA/input/test_1.in > /home/felipecarpes/exerciciosREVISAO/MONITORIA/myoutput/test_1.out
	./main < /home/felipecarpes/exerciciosREVISAO/MONITORIA/input/test_2.in > /home/felipecarpes/exerciciosREVISAO/MONITORIA/myoutput/test_2.out
	./main < /home/felipecarpes/exerciciosREVISAO/MONITORIA/input/test_3.in > /home/felipecarpes/exerciciosREVISAO/MONITORIA/myoutput/test_3.out
	diff myoutput/ output/
clean: 
	@ echo "\033[1;35m"
	@ echo "Removing temporary files ..."
	@ rm -rf $(NAME_PROGRAM) $(O_FILES)
	@ echo "\033[0m"
	