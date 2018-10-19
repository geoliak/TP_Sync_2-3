#include "lecteur_redacteur.h"

initialiser_lecteur_redacteur(lecteur_redacteur_t lc){
	lc->etat = 0;
	lc->verrou = pthread_mutex_init();
	lc->condition = pthread_cond_init();
