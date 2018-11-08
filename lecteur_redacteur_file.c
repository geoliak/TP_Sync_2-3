#include "lecteur_redacteur_file.h"

void debut_lecture(lecteur_redacteur_t *lec_red){
	//printf("Arrivee du thread lecteur %x\n", (int) pthread_self());


	pthread_mutex_lock(&lec_red->verrou_global);
	//incrémentation du nombre de lecteurs en attente
	if(lec_red->file_tete != NULL) {
		//Ajout d'une nouvelle condition dans la queue de la file
		file_cond* newcond = malloc(sizeof(file_cond));
		pthread_cond_init(&newcond->cond,NULL);
		newcond->est_lecteur = 1;
		newcond->next = NULL;
		lec_red->file_queue->next = newcond;
		lec_red->file_queue = newcond;
		pthread_cond_wait(&lec_red->file_queue->cond,&lec_red->verrou_global); //on attend sur la condition
		
		pthread_mutex_lock(&lec_red->verrou_global);
		
		if(lec_red->file_tete->est_lecteur == 1){
			pthread_cond_signal(&lec_red->file_tete->cond);
			if(lec_red->file_tete->next != NULL)
				lec_red->file_tete = lec_red->file_tete->next;
			else lec_red->file_tete = NULL;
		}
	}
	else if(lec_red->redaction_en_cours == 1){
		//Ajout d'une nouvelle condition et initialisation de la file vide
		file_cond* newcond = malloc(sizeof(file_cond));
		pthread_cond_init(&newcond->cond,NULL);
		newcond->est_lecteur = 1;
		newcond->next = NULL;
		lec_red->file_tete = newcond;
		lec_red->file_queue = newcond;
		pthread_cond_wait(&lec_red->file_queue->cond,&lec_red->verrou_global);
	}
	lec_red->lectures_en_cours++;
	pthread_mutex_unlock(&lec_red->verrou_global);
}

void fin_lecture(lecteur_redacteur_t *lec_red){
	pthread_mutex_lock(&lec_red->verrou_global);
	lec_red->lectures_en_cours--;

	if(lec_red->file_tete != NULL && lec_red->lectures_en_cours == 0){
		pthread_cond_signal(&lec_red->file_tete->cond);
		if(lec_red->file_tete->next != NULL){
			lec_red->file_tete = lec_red->file_tete->next;
		}
		else lec_red->file_tete = NULL;
	}
	pthread_mutex_unlock(&lec_red->verrou_global);
}

void debut_redaction(lecteur_redacteur_t *lec_red){
	pthread_mutex_lock(&lec_red->verrou_global);

	if(lec_red->file_tete != NULL) {
		//Ajout d'une nouvelle condition dans la queue de la file
		file_cond* newcond = malloc(sizeof(file_cond));
		pthread_cond_init(&newcond->cond,NULL);
		newcond->est_lecteur = 0;
		newcond->next = NULL;
		lec_red->file_queue->next = newcond;
		lec_red->file_queue = newcond;
		pthread_cond_wait(&lec_red->file_queue->cond,&lec_red->verrou_global); //on attend sur la condition
		
		pthread_mutex_lock(&lec_red->verrou_global);
	}
	
	else if(lec_red->lectures_en_cours != 0 || lec_red->redaction_en_cours == 1){
		//Ajout d'une nouvelle condition et initialisation de la file vide
		file_cond* newcond = malloc(sizeof(file_cond));
		pthread_cond_init(&newcond->cond,NULL);
		newcond->est_lecteur = 0;
		newcond->next = NULL;
		lec_red->file_tete = newcond;
		lec_red->file_queue = newcond;
		pthread_cond_wait(&lec_red->file_queue->cond,&lec_red->verrou_global);
	}

	lec_red->redaction_en_cours = 1;
	pthread_mutex_unlock(&lec_red->verrou_global);
}

void fin_redaction(lecteur_redacteur_t *lec_red) {
	pthread_mutex_lock(&lec_red->verrou_global);
	lec_red->redaction_en_cours--;
	if(lec_red->file_tete != NULL){
		pthread_cond_signal(&lec_red->file_tete->cond);
		if(lec_red->file_tete->next != NULL){
			lec_red->file_tete = lec_red->file_tete->next;
		}
		else lec_red->file_tete = NULL;
	}
	pthread_mutex_unlock(&lec_red->verrou_global);
}

void initialiser_lecteur_redacteur(lecteur_redacteur_t *lc){
	lc->lectures_en_cours = 0;
	lc->redaction_en_cours = 0;
	pthread_mutex_init(&lc->verrou_global,NULL);
	lc->file_tete = NULL;
	lc->file_queue = NULL;
}
void detruire_lecteur_redacteur(lecteur_redacteur_t *lec_red){
	pthread_mutex_destroy(&lec_red->verrou_global);
}
