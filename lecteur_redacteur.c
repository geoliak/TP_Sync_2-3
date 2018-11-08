#include "lecteur_redacteur.h"


int lecteur_en_attente = 0 ;


void debut_lecture(lecteur_redacteur_t *lec_red){
	//si nb_lecteurs = 0 alors wait sur le sémaphore puis nb_lecteurs++, sinon seulement nb_lecteurs++
	pthread_mutex_lock(&lec_red->verrou_global);
	lecteur_en_attente = 1;
	if (lec_red->nb_lecteurs==0) {
		sem_wait(&lec_red->sem);
	}
	lecteur_en_attente = 0;
	lec_red->nb_lecteurs++;
	pthread_mutex_unlock(&lec_red->verrou_global);
}

void fin_lecture(lecteur_redacteur_t *lec_red){
	pthread_mutex_lock(&lec_red->verrou_global);
	//si il reste un autre lecteur on décrémente juste nb_lecteurs. Sinon on envoie également un signal
	lec_red->nb_lecteurs--;
	if (lec_red->nb_lecteurs==0) {
		sem_post(&lec_red->sem);
	}
	pthread_mutex_unlock(&lec_red->verrou_global);
}

void debut_redaction(lecteur_redacteur_t *lec_red){
	//wait sur le sémaphore dans tout les cas
	sem_wait(&lec_red->sem);
	while (lecteur_en_attente != 0) {
		sem_post(&lec_red->sem);
		sem_wait(&lec_red->sem);
	}

}

void fin_redaction(lecteur_redacteur_t *lec_red){
	sem_post(&lec_red->sem);
}

void initialiser_lecteur_redacteur(lecteur_redacteur_t *lc){
	lc->nb_lecteurs = 0;
	pthread_mutex_init(&lc->verrou_global,NULL);
	sem_init(&lc->sem,0,1);
}
void detruire_lecteur_redacteur(lecteur_redacteur_t *lec_red){
	sem_destroy(&lec_red->sem);
	pthread_mutex_destroy(&lec_red->verrou_global);

}
