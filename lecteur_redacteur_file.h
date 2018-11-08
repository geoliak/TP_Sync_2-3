#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct file_cond {
	pthread_cond_t	cond;
	struct file_cond* next;	
	int est_lecteur;
}file_cond;

typedef struct lecteur_redacteur_t {
	pthread_mutex_t verrou_global;
	file_cond* file_tete;
	file_cond* file_queue;
	int lectures_en_cours;
	int redaction_en_cours;

}lecteur_redacteur_t;


void debut_lecture(lecteur_redacteur_t *lec_red);
void fin_lecture(lecteur_redacteur_t *lec_red);
void debut_redaction(lecteur_redacteur_t *lec_red);
void fin_redaction(lecteur_redacteur_t *lec_red);

void initialiser_lecteur_redacteur(lecteur_redacteur_t *lec_red);
void detruire_lecteur_redacteur(lecteur_redacteur_t *lec_red);
