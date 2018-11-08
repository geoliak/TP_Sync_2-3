CC=gcc
CFLAGS=-Wall -Werror -g -lm
LDLIBS=-lpthread

all:	test_lecteurs_prioritaires test_redacteurs_prioritaires test_lecteurs_redacteurs_file

test_lecteurs_redacteurs_file:	test_lecteurs_redacteurs_file.o lecteur_redacteur_file.o

test_lecteurs_prioritaires:	test_lecteurs_prioritaires.o lecteur_prioritaire.o lecteur_prioritaire.h

test_redacteurs_prioritaires:	test_redacteurs_prioritaires.o redacteur_prioritaire.o redacteur_prioritaire.h
	gcc   test_redacteurs_prioritaires.o redacteur_prioritaire.o redacteur_prioritaire.h  -lpthread -o test_redacteurs_prioritaires
	
redacteur_prioritaire.o:	redacteur_prioritaire.c
	$(CC) $(CFLAGS) -c redacteur_prioritaire.c

lecteur_prioritaire.o:	lecteur_prioritaire.c lecteur_prioritaire.h
	$(CC) $(CFLAGS) -c lecteur_prioritaire.c

test_lecteurs_prioritaires.o:		test_lecteurs_prioritaires.c
	$(CC) $(CFLAGS) -c test_lecteurs_prioritaires.c

test_redacteurs_prioritaires.o:		test_redacteurs_prioritaires.c
	$(CC) $(CFLAGS) -c test_redacteurs_prioritaires.c

clean:
	rm test_lecteurs_redacteurs_file test_lecteurs_prioritaires test_redacteurs_prioritaires *.o
