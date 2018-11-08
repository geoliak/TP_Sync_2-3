#include "redacteur_prioritaire.h"


void debut_lecture(lecteur_redacteur_t *lec_red){
	//printf("Arrivee du thread lecteur %x\n", (int) pthread_self());


	pthread_mutex_lock(&lec_red->verrou_global);
	//incrémentation du nombre de lecteurs en attente
	lec_red->nb_lecteurs++;
	while (lec_red->nb_redacteurs !=0 ) {
		pthread_cond_wait(&lec_red->cond_lect,&lec_red->verrou_global);
	}
	lec_red->lectures_en_cours++;
	pthread_mutex_unlock(&lec_red->verrou_global);
}

void fin_lecture(lecteur_redacteur_t *lec_red){
	pthread_mutex_lock(&lec_red->verrou_global);


	lec_red->nb_lecteurs--;
	lec_red->lectures_en_cours--;
	pthread_cond_broadcast(&lec_red->cond_reda);
	pthread_cond_broadcast(&lec_red->cond_lect);
	
	pthread_mutex_unlock(&lec_red->verrou_global);
}

void debut_redaction(lecteur_redacteur_t *lec_red){
	//printf("Arrivee du thread redacteur %x\n", (int) pthread_self());
	pthread_mutex_lock(&lec_red->verrou_global);
	lec_red->nb_redacteurs++;
	while (lec_red->lectures_en_cours != 0) {
		pthread_cond_wait(&lec_red->cond_reda,&lec_red->verrou_global);
	}
//	pthread_mutex_unlock(&lec_red->verrou_global);
}

void fin_redaction(lecteur_redacteur_t *lec_red) {
//	pthread_mutex_lock(&lec_red->verrou_global);
	lec_red->nb_redacteurs--;
	pthread_cond_broadcast(&lec_red->cond_reda);
	pthread_cond_broadcast(&lec_red->cond_lect);
	pthread_mutex_unlock(&lec_red->verrou_global);

}

void initialiser_lecteur_redacteur(lecteur_redacteur_t *lc){
	lc->nb_lecteurs = 0;
	lc->nb_redacteurs = 0;
	lc->lectures_en_cours = 0;
	pthread_mutex_init(&lc->verrou_global,NULL);
	pthread_cond_init(&lc->cond_lect,NULL);
	pthread_cond_init(&lc->cond_reda,NULL);
}
void detruire_lecteur_redacteur(lecteur_redacteur_t *lec_red){
	pthread_mutex_destroy(&lec_red->verrou_global);
	pthread_cond_destroy(&lec_red->cond_lect);
	pthread_cond_destroy(&lec_red->cond_reda);
}
