CC=gcc
CFLAGS=-Wall -Werror -g -lm
LDLIBS=-lpthread

all:	test_lecteurs_redacteurs test_redacteurs_prioritaires

test_lecteurs_redacteurs:	test_lecteurs_redacteurs.o lecteur_redacteur.o lecteur_redacteur.h

test_redacteurs_prioritaires:	test_redacteurs_prioritaires.o redacteur_prioritaire.o redacteur_prioritaire.h
	gcc   test_redacteurs_prioritaires.o redacteur_prioritaire.o redacteur_prioritaire.h  -lpthread -o test_redacteurs_prioritaires
	
redacteur_prioritaire.o:	redacteur_prioritaire.c
	$(CC) $(CFLAGS) -c redacteur_prioritaire.c

lecteur_redacteur.o:	lecteur_redacteur.c lecteur_redacteur.h
	$(CC) $(CFLAGS) -c lecteur_redacteur.c

test_lecteurs_redacteurs.o:		test_lecteurs_redacteurs.c
	$(CC) $(CFLAGS) -c test_lecteurs_redacteurs.c

test_redacteurs_prioritaires.o:		test_redacteurs_prioritaires.c
	$(CC) $(CFLAGS) -c test_redacteurs_prioritaires.c

clean:
	rm test_lecteurs_redacteurs test_lecteur_prioritaire test_redacteurs_prioritaires *.o
