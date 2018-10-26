CC=gcc
CFLAGS=-Wall -Werror -g -lm
LDLIBS=-lpthread

all:	test_lecteurs_redacteurs

test_lecteurs_redacteurs:	test_lecteurs_redacteurs.o lecteur_redacteur.o

lecteur_redacteur.o:
	$(CC) $(CFLAGS) -c lecteur_redacteur.c 

clean:
	rm test_lecteurs_redacteurs *.o 
