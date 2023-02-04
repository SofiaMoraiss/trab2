all: programa

%.o: %.c %.h
	gcc -c $< -o $@

libminerador.a: minerador/tDocumento.o minerador/tListas.o minerador/tPalavra.o minerador/tHashPalavras.o
	ar -crs libminerador.a minerador/tDocumento.o minerador/tListas.o minerador/tPalavra.o minerador/tHashPalavras.o

programa: indice.c buscador.c libminerador.a
	@gcc -L. indice.c -o indice  -I minerador -lminerador  -lm
	@gcc -L. buscador.c -o buscador  -I minerador -lminerador  -lm

clean:
	@rm -f main libminerador minerador.a minerador/*.o *.o
val1:
	@valgrind --leak-check=full --track-origins=yes ./indice medium-large/train.txt indice.bin > output.txt1
val2:
	@valgrind --leak-check=full ./buscador indice.bin > output.txt2
run1:
	@./indice tiny/train.txt indice.bin > output.txt1
run2:
	@./buscador indice.bin > output.txt2
