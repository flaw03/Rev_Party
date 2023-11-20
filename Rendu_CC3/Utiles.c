#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Utiles.h"



struct s_Candidat {
    char* nom;
    char* prenom;
    int age;
    int vote;
    struct s_Candidat *next;
};

struct s_Electeur {
    char* nom;
    char* prenom;
    struct s_Candidat *candidat;
    struct s_Electeur *next;
};

struct s_List_Electeur {
    struct s_Electeur *head;
    struct s_Electeur *tail;
    unsigned int size;
};

struct s_List_Cand {
    struct s_Candidat *head;
    struct s_Candidat *tail;
    unsigned int size;
};

Electeur* create_electeur(const char* nom, const char* prenom, Candidat* candidat) {
    Electeur *new = malloc(sizeof(Electeur));
    new->nom = strdup(nom);        // Utilisation de strdup pour dupliquer la chaîne
    new->prenom = strdup(prenom);  // Utilisation de strdup pour dupliquer la chaîne
    new->candidat = candidat;
    new->next = NULL;
    return new;
}


ListElect *listElect_create(){
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



ListCand *listCand_create(){
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
        free(current->nom);     // Libération de la mémoire allouée par strdup
        free(current->prenom);  // Libération de la mémoire allouée par strdup
        free(current);
        current = next;
    }
    free(l);
}


void printList(ListCand *l){
    for(Candidat* c = l->head;c!=NULL;c = c->next){
        printf("Candidat: %s %s age %d\n",c->nom,c->prenom,c->age);
    }
}


