/*-----------------------------------------------------------------*/
/*
 Implantation du TAD List .
 */
/*-----------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"
#include "utils_tab.h"

typedef struct s_LinkedElement {
  struct  s_element * element;
	struct s_LinkedElement *previous;
	struct s_LinkedElement *next;
} LinkedElement;

struct s_List {
	LinkedElement *sentinel;
	int size;
};


/*-----------------------------------------------------------------*/

List *list_create(void) {
	List *l = malloc(sizeof(struct s_List));
  l->sentinel=malloc(sizeof(LinkedElement));
  l->sentinel->next=l->sentinel->previous=l->sentinel;
  l->size=0;
	return l;
}

/*-----------------------------------------------------------------*/

List *list_push_back(List *l, int p, int candidat1, int candidat2) {
	LinkedElement *new= malloc(sizeof(LinkedElement));
  Element e = malloc(sizeof(struct s_element ));
  e->a = candidat1;
  e->b = candidat2;
  e->p = p;
  new->element = e;
  new->next=l->sentinel;
  new->previous=new->next->previous;
  new->next->previous=new;
  new->previous->next=new;
  ++(l->size);
	return l;
}

/*-----------------------------------------------------------------*/

void list_delete(ptrList *l) {
  free(*l);
	*l=NULL;
}

/*-----------------------------------------------------------------*/

List *list_push_front(List *l, int p, int candidat1, int candidat2) {
	LinkedElement *new= malloc(sizeof(LinkedElement));
  Element e = malloc(sizeof(struct s_element ));
  e->a = candidat1;
  e->b = candidat2;
  e->p = p;
  new->element = e;
  new->previous=l->sentinel;
  new->next=new->previous->next;
  new->next->previous=new;
  new->previous->next=new;
  ++(l->size);
	return l;
}

/*-----------------------------------------------------------------*/

/*int list_front(List *l) {
	assert(!list_is_empty(l));
	return l->sentinel->next->value;
}*/

/*-----------------------------------------------------------------*/

/*int list_back(List *l) {
	assert(!list_is_empty(l));
	return l->sentinel->previous->value;
}*/

/*-----------------------------------------------------------------*/

List *list_pop_front(List *l) {
  assert(!list_is_empty(l));
  LinkedElement *old=l->sentinel->next;
  l->sentinel->next=old->next;
  l->sentinel->next->previous=l->sentinel;
  l->sentinel->previous->next=l->sentinel;
  --(l->size);
  free(old);
	return l;
}

/*-----------------------------------------------------------------*/

List *list_pop_back(List *l){
  assert(!list_is_empty(l));
  LinkedElement *old=l->sentinel->previous;
  l->sentinel->previous=old->previous;
  l->sentinel->previous->next=l->sentinel;
  l->sentinel->next->previous=l->sentinel;
  --(l->size);
  free(old);
	return l;
}

/*-----------------------------------------------------------------*/

List *list_insert_at(List *l, int pos, int p, int candidat1, int candidat2) {
  assert(pos>=0 && pos<=l->size);
	LinkedElement *new=malloc(sizeof(LinkedElement));
  LinkedElement *e=l->sentinel->next;
  Element e = malloc(sizeof(struct s_element ));
  e->a = candidat1;
  e->b = candidat2;
  e->p = p;
  new->element = e;

  for(int i=0;i<p; ++i){
    e=e->next;
  }

  new->next=e;
  new->previous=e->previous;
  e->previous=new;
  new->previous->next=new;
  new->next->previous=new;
  ++(l->size);
	return l;
}

/*-----------------------------------------------------------------*/

List *list_remove_at(List *l, int p) {
	assert(p>=0 && p<=l->size);
  LinkedElement *e=l->sentinel->next;
  LinkedElement *old;
	for (int i=0; i< p; ++i) {
    e=e->next;
  }
  old=e;
  e->previous->next=old->next;
  e->next->previous=old->previous;
  --(l->size);
  free(old->element);
  free(old);
	return l;
}

/*-----------------------------------------------------------------*/

/*int list_at(List *l, int p) {
  assert(p>=0 && p<l->size);
  int val;
  LinkedElement *e=l->sentinel->next;
	for (int i=0; i< p; ++i) {
    e=e->next;
  }

  val=e->value;
	return val;
}*/

/*-----------------------------------------------------------------*/

bool list_is_empty(List *l) {
	return l->size==0;
}

/*-----------------------------------------------------------------*/

int list_size(List *l) {
	return l->size;
}

/*-----------------------------------------------------------------*/

/*
List * list_map(List *l, SimpleFunctor f) {
	for (LinkedElement *e=l->sentinel->next; e!=l->sentinel; e=e->next){
    e->value=f(e->value);
  }
	return l;
}

*/


List *list_reduce(List *l, ReduceFunctor f,void * env) {
  for (LinkedElement *e=l->sentinel->next; e!=l->sentinel; e=e->next){
    f(e->element,env);
  }
	return l;
}

List * matriceCombatToGraphe(Matrice matrice){    
    List *list = list_create();
    for (int i = 0; i < matrice->nb_ligne;i++){
        for (int j = 0; j < matrice->nb_colonne;j++){
            if (i != j){
                if (matrice->tableau[i][j] >= matrice->tableau[j][i]){
                    list_push_front(list,matrice->tableau[i][j],i,j);
                }
            }
        }
    }
    return list;
}

// Fait la somme des de chaque sommet 
void Vainquqeur(List * list,Matrice matrice){
    for (LinkedElement *e = list->sentinel->next; e != list->sentinel; e = e->next){
      matrice->tableau[0][e->a]++;
    }
}
