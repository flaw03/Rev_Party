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
	int poids;
	int a;
	int b;
	struct s_LinkedElement *previous;
	struct s_LinkedElement *next;
} LinkedElement;

struct s_List {
	LinkedElement* sentinel;
	int size;
};


/*-----------------------------------------------------------------*/

List *list_create() {
	List *l = malloc(sizeof(struct s_List));
  l->sentinel=malloc(sizeof(LinkedElement));
  l->sentinel->next=l->sentinel->previous=l->sentinel;
  l->size=0;
	return l;
}

/*-----------------------------------------------------------------*/

List *list_push_back(List *l, int p, int candidat1, int candidat2) {
	LinkedElement *new= malloc(sizeof(LinkedElement));
  new->poids=p;
  new->a=candidat1;
  new->b=candidat2;
  new->next=l->sentinel;
  new->previous=new->next->previous;
  new->next->previous=new;
  new->previous->next=new;
  ++(l->size);
	return l;
}

/*-----------------------------------------------------------------*/

void list_delete(ptrList *l) {
  while(!list_is_empty(*l)){
    list_pop_back(*l);
  }
  free(*l);
	*l=NULL;
}

/*-----------------------------------------------------------------*/

List *list_push_front(List *l, int p, int candidat1, int candidat2) {
	LinkedElement *new= malloc(sizeof(LinkedElement));
  new->poids=p;
  new->a=candidat1;
  new->b=candidat2;
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
  new->poids=p;
  new->a=candidat1;
  new->b=candidat2;

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

bool list_iterator_end(ListIterator it){
  return it->current==it->collection->sentinel;
}

ListIterator list_iterator_next(ListIterator it){
  it->current=it->next(it->current);
  return it;
}

int list_iterator_value(ListIterator it){
  return it->current->a;
}



int main(void)
{
  List* l=list_create();
  l=list_push_back(l,1,12,2);
  printf("size %d\n", list_size(l));
  l=list_pop_back(l);
  printf("size %d\n", list_size(l));
  return 0;
}