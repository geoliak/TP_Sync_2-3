#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct lecteur_redacteur_t {
	
	pthread_cond_t condition;
	int etat = 0; // 0:attente 1:lecture 2:wait 3:lecture_seule
	pthread_mutex_t verrou;
	
	}lecteur_redacteur_t;

void debut_lecture(lecteur_redacteur_t *lec_red);
void fin_lecture(lecteur_redacteur_t *lec_red);

void initialiser_lecteur_redacteur(lecteur_redacteur_t lec_red);
void detruire_lecteur_redacteur(lecteur_redacteur_t lec_red);
