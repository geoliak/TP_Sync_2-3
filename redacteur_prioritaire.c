#include "lecteur_redacteur.h"


void debut_lecture(lecteur_redacteur_t *lec_red){
	//printf("Arrivee du thread lecteur %x\n", (int) pthread_self());
	//si nb_lecteurs = 0 alors wait sur le sémaphore puis nb_lecteurs++, sinon seulement nb_lecteurs++
	pthread_mutex_lock(&lec_red->verrou_global);
	//incrémentation du nombre de lecteurs en attente
	lec_red->nb_lecteurs++;
	while (lec_red->nb_redacteurs!=0) {
		pthread_cond_wait(&lec_red->cond_lect,&lec_red->verrou_global);
	}
	pthread_mutex_unlock(&lec_red->verrou_global);
}

void fin_lecture(lecteur_redacteur_t *lec_red){
	pthread_mutex_lock(&lec_red->verrou_global);
	//si il reste un autre lecteur on décrémente juste nb_lecteurs. Sinon on envoie également un signal
	lec_red->nb_lecteurs--;
	if (lec_red->nb_lecteurs==0) {
		pthread_cond_broadcast(&lec_red->cond_reda);
	}
	pthread_mutex_unlock(&lec_red->verrou_global);
}

void debut_redaction(lecteur_redacteur_t *lec_red){
	//printf("Arrivee du thread redacteur %x\n", (int) pthread_self());
	pthread_mutex_lock(&lec_red->verrou_global);
	while (lec_red->lecteur_en_attente != 0 || lec_red->nb_redacteurs!= 0) {
		pthread_cond_wait(&lec_red->cond_reda,&lec_red->verrou_global);
	}
	lec_red->nb_redacteurs++;
	pthread_mutex_unlock(&lec_red->verrou_global);
}

void fin_redaction(lecteur_redacteur_t *lec_red) {
	pthread_mutex_lock(&lec_red->verrou_global);
	lec_red->nb_redacteurs--;
	if (lec_red->lecteur_en_attente>0) {
		pthread_cond_broadcast(&lec_red->cond_lect);
	}
	else{
		pthread_cond_broadcast(&lec_red->cond_lect);
	}
	pthread_mutex_unlock(&lec_red->verrou_global);

}

void initialiser_lecteur_redacteur(lecteur_redacteur_t *lc){
	lc->nb_lecteurs = 0;
	lc->nb_redacteurs = 0;
	pthread_mutex_init(&lc->verrou_global,NULL);
	lc->lecteur_en_attente = 0;
	pthread_cond_init(&lc->cond_lect,NULL);
	pthread_cond_init(&lc->cond_reda,NULL);
}
void detruire_lecteur_redacteur(lecteur_redacteur_t *lec_red){
	pthread_mutex_destroy(&lec_red->verrou_global);
	//pthread_cond_destroy(&lec_red->cond_lect);
}
