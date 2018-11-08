#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


typedef struct lecteur_redacteur_t {
	pthread_mutex_t verrou_global;
	pthread_cond_t cond_lect;
	pthread_cond_t cond_reda;
	int nb_lecteurs;
	int nb_redacteurs;
	int lectures_en_cours;
}lecteur_redacteur_t;

void debut_lecture(lecteur_redacteur_t *lec_red);
void fin_lecture(lecteur_redacteur_t *lec_red);
void debut_redaction(lecteur_redacteur_t *lec_red);
void fin_redaction(lecteur_redacteur_t *lec_red);

void initialiser_lecteur_redacteur(lecteur_redacteur_t *lec_red);
void detruire_lecteur_redacteur(lecteur_redacteur_t *lec_red);
