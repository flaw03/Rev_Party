/*-----------------------------------------------------------------*/
/*
 Implantation du TAD List .
 */
/*-----------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct s_LinkedElement {
  struct  s_element * element;
	struct s_LinkedElement *previous;
	struct s_LinkedElement *next;
} LinkedElement;

struct s_List {
	LinkedElement* sentinel;
	int size;
};


/*-----------------------------------------------------------------*/

List *list_create(void) {
	List *l = malloc(sizeof(struct s_List));
  l->sentinel=malloc(sizeof(LinkedElement));
  l->sentinel->next=l->sentinel->previous=l->sentinel;
  l->sentinel->element = NULL; 
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

void list_delete(ptrList *l){
	LinkedElement *e = (*l)->sentinel->next;
	LinkedElement *f;
	while (e != (*l)->sentinel){
		f = e;
		e = e->next;
        free(f->element);
		free(f);
	}
	free(e);
	free(*l);
	*l = NULL;
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
    Element element = malloc(sizeof(struct s_element ));
    element->a = candidat1;
    element->b = candidat2;
    element->p = p;
    new->element = element;

    for(int i=0;i<pos; ++i){
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

LinkedElement* list_at_aux(List *l, int p) {
    assert(p>=0 && p<l->size);
    //int val;
    LinkedElement *e=l->sentinel->next;
	for (int i=0; i< p; ++i) {
        e=e->next;
    }
    //val=e->value;
	return e;
}

/*-----------------------------------------------------------------*/

bool list_is_empty(List *l) {
	return l->size==0;
}

/*-----------------------------------------------------------------*/

int list_size(List *l) {
	return l->size;
}

/*-----------------------------------------------------------------*/

/*List * list_map(List *l, SimpleFunctor f) {
	for (LinkedElement *e=l->sentinel->next; e!=l->sentinel; e=e->next){
    e->value=f(e->value);
  }
	return l;
}


List *list_reduce(List *l, ReduceFunctor f, void *userData) {
  for (LinkedElement *e=l->sentinel->next; e!=l->sentinel; e=e->next){
    f(e->value,userData);
  }
	return l;
}*/
// iterator
struct s_ListIterator{
    List* collection;
    LinkedElement* begin;
    LinkedElement* current;
    LinkedElement* (*next)(LinkedElement*);
};

LinkedElement* goto_next(LinkedElement* e){
    return e->next;
}

LinkedElement* goto_previous(LinkedElement* e){
    return e->previous;
}

ListIterator list_iterator_create(List* d, unsigned char w){
    ListIterator it= malloc(sizeof(struct s_ListIterator));
    it->collection=d;
    if(w==FORWARD_ITERATOR){
        it->begin=d->sentinel->next;
        it->next=goto_next;
    }else{
        it->begin=d->sentinel->previous;
        it->next=goto_previous;
    }
    it->current=it->begin;
    return it;
}

void list_iterator_delete(ListIterator it){
    free(it);
}

ListIterator list_iterator_begin(ListIterator it){
    it->current=it->begin;
    return it;
}

int list_iterator_end(ListIterator it){
    return it->current== it->collection->sentinel;
}

int list_iterator_has_next(ListIterator it){
    return it->next(it->current) == it->collection->sentinel;
}

Element list_iterator_next(ListIterator it){
    it->current=it->next(it->current);
    return it->current->element;
}

Element list_iterator_value(ListIterator it){
  return it->current->element;
}

int list_iterator_delete_current(ListIterator it){
    LinkedElement *e = it->current;
    if (e == it->begin){
        if (e == it->collection->sentinel->next){
            it->begin = e->next;
        }else{
            it->begin = e->previous;
        } 
    }
    list_iterator_next(it);
    e->previous->next = e->next;
    e->next->previous = e->previous;
    it->collection->size --;
    free(e->element);
    free(e);
    return 1;
}


List *list_reduce(List *l, ReduceFunctor f,void * env) {
    for (LinkedElement *e=l->sentinel->next; e!=l->sentinel; e=e->next){
        f(e->element,env);
    }
    return l;
}

List * matriceCombatToGraphe(Matrice matriceDuel){    
    List *list = list_create();
    for (int i = 0; i < matriceDuel->nb_ligne;i++){
        for (int j = 0; j < matriceDuel->nb_colonne;j++){
            if (i != j){
                if (matriceDuel->tableau[i][j] >= matriceDuel->tableau[j][i]){
                    list_push_front(list,matriceDuel->tableau[i][j],i,j);
                }
            }
        }
    }
    return list;
}

int triee_liste_decroissant(List* l){
  LinkedElement *from, *to;
  Element aux= malloc(sizeof(Element));
  for(int i=0;i<l->size;i++){
    from= list_at_aux(l,i);
    for(int j=i+1; j<l->size; j++){
      to=list_at_aux(l,j);
      if(from->element->p< to->element->p){
        *aux=*(from->element);
        *(from->element)=*(to->element);
        *(to->element)=*aux;
      }
    }
  }
  
  free(aux);
    for(LinkedElement* e= l->sentinel->next; e->next!=l->sentinel; e=e->next){
      if(e->element->p<e->next->element->p){
        return 0;
      }
  }
  return 1;
}