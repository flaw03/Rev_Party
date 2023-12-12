#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "utiles.h"
#include "utils_tab.h"


/********************************************************/
Electeur* create_electeur(const char* nom, const char* prenom, Candidat* candidat) {
    Electeur *new = malloc(sizeof(Electeur));
    new->nom = strdup(nom);        // Utilisation de strdup pour dupliquer la chaîne
    new->prenom = strdup(prenom);  // Utilisation de strdup pour dupliquer la chaîne
    new->candidat = candidat;
    new->next = NULL;
    return new;
}


ListElect *listElect_create(void){
  ListElect *l = malloc(sizeof(ListElect));
  l-> head = l-> tail = NULL;
  l->size = 0;
  return l;
}


ListElect *list_add_Electeur(ListElect* l, Electeur* electeur){
  Electeur **insert_at = (l->size ? &(l->tail->next):&(l->head));
  electeur->next = NULL;
  *insert_at = l->tail = electeur;
  l->size++;
  return l;
}


void listElect_delete(ListElect* l) {
    Electeur* current = l->head;
    while (current != NULL) {
        Electeur* next = current->next;
        free(current->nom);       // Libération de la mémoire allouée par strdup
        free(current->prenom);    // Libération de la mémoire allouée par strdup
        free(current);
        current = next;
    }
    free(l);
}
/********************************************************/

/********************************************************/
ListCand *listCand_create(void){
  ListCand *l = malloc(sizeof(ListCand));
  l-> head = l-> tail = NULL;
  l->size = 0;
  return l;
}

Candidat* create_candidat(const char* nom, const char* prenom, int age) {
    Candidat *new = (Candidat*)malloc(sizeof(Candidat));
    new->nom = strdup(nom);        // Utilisation de strdup pour dupliquer la chaîne
    new->prenom = strdup(prenom);  // Utilisation de strdup pour dupliquer la chaîne
    new->age = age;
    new->next = NULL;
    new->jugement = NULL;
    new->vote = 0;
    return new;
}

ListCand *listCand_add(ListCand* l, Candidat *candidat){
  Candidat **insert_at = (l->size ? &(l->tail->next):&(l->head));
  candidat->next = NULL;
  *insert_at = l->tail = candidat;
  l->size++;
  return l;
}


void listCand_delete(ListCand* l) {
    Candidat* current = l->head;
    while (current != NULL) {
        Candidat* next = current->next;
        if (current->jugement != NULL){
            delete_Tableau(current->jugement);
        }
        free(current->nom);     // Libération de la mémoire allouée par strdup
        free(current->prenom);  // Libération de la mémoire allouée par strdup
        free(current);
        current = next;
    }
    free(l);
}
/********************************************************/
/********************************************************/
void tableauDelete(ListCand* l){
  for(Candidat* c = l->head;c!=NULL;c = c->next){
    delete_Tableau(c->jugement);
  }

}

/********************************************************/
void printList(ListCand *l){
    for(Candidat* c = l->head;c!=NULL;c = c->next){
        printf("Candidat: %s %s age %d\n",c->nom,c->prenom,c->age);
    }
}
/********************************************************/
int getIndiceVote(Tableau tab){
    int cpt = 0;
    int min = tab->tableau[0];
    for(int i = 0;i<tab->dim;i++){
        if(tab->tableau[i]<min && tab->tableau[i] != -1){
            cpt=i;
            min = tab->tableau[i];
        }
    }
    return cpt;
}

/********************************************************/
Candidat* candidatAssocie(int nb,ListCand* lstCand){
    if((unsigned int)nb>lstCand->size){
    	fprintf(stderr,"Indice candidat invalide");
    	exit(18);
    }
    Candidat* candidat = lstCand->head;
    for(int i = 0;i<nb;i++){
        candidat = candidat->next;
    }
    return candidat;
}

/********************************************************/
void createTableau(int taille,ListCand* lstCand){
    for(Candidat* c = lstCand->head;c!=NULL;c = c->next){
        c->jugement = create_Tableau(taille);
    }
}
/********************************************************/
int isInteger(const char *str) {
    // Vérifie si la chaîne est un entier
    int i = 0;
    while (str[i]) {
        if (!isdigit(str[i])) {
            return 0;
        }
        i++;
    }
    return 1;
}

