#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct lecteur_redacteur_t {
	//pthread_cond_t condition;
	pthread_mutex_t verrou_global;
	int nb_lecteurs;
	sem_t sem;
}lecteur_redacteur_t;

void debut_lecture(lecteur_redacteur_t *lec_red);
void fin_lecture(lecteur_redacteur_t *lec_red);
void debut_redaction(lecteur_redacteur_t *lec_red);
void fin_redaction(lecteur_redacteur_t *lec_red);

void initialiser_lecteur_redacteur(lecteur_redacteur_t *lec_red);
void detruire_lecteur_redacteur(lecteur_redacteur_t *lec_red);
