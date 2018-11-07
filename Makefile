CC=gcc
CFLAGS=-Wall -Werror -g -lm -fno-stack-protector
LDLIBS=-lpthread

all:	test_lecteurs_redacteurs 

test_lecteurs_redacteurs:	test_lecteurs_redacteurs.o lecteur_redacteur.o lecteur_redacteur.h

test_redacteurs_prioritaires:	test_lecteurs_redacteurs.o redacteur_prioritaire.o
	$(CC) $(CFLAGS) $(LDLIBS) test_lecteurs_redacteurs.o redacteur_prioritaire.o
	
redacteur_prioritaire.o:	redacteur_prioritaire.c
	$(CC) $(CFLAGS) -c redacteur_prioritaire.c

lecteur_redacteur.o:	lecteur_redacteur.c lecteur_redacteur.h
	$(CC) $(CFLAGS) -c lecteur_redacteur.c

test_lecteurs_redacteurs.o:		test_lecteurs_redacteurs.c
	$(CC) $(CFLAGS) -c test_lecteurs_redacteurs.c

clean:
	rm test_lecteurs_redacteurs *.o
