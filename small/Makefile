all: programa

%.o: %.c %.h
	gcc -c $< -o $@

libspotify.a: spotify/tDocumento.o spotify/tListas.o spotify/tPalavra.o spotify/tHashPalavras.o
	ar -crs libspotify.a spotify/tDocumento.o spotify/tListas.o spotify/tPalavra.o spotify/tHashPalavras.o

programa: indice.c buscador.c libspotify.a
	gcc -L. indice.c -o indice  -I spotify -lspotify  -lm
	gcc -L. buscador.c -o buscador  -I spotify -lspotify  -lm

clean:
	rm -f main libspotify spotify.a spotify/*.o *.o

run:
	./main tracks_full.csv artists_full.csv