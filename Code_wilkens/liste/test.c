#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

int main(void)
{
  List* l=list_create();
  l=list_push_back(l,1,2,3);
  l=list_push_back(l,2,2,4);
  l=list_push_back(l,3,2,5);
  l=list_push_back(l,4,2,6);
  printf("size %d\n", list_size(l));
  int poids;
  ListIterator it= list_iterator_create(l,1);
  //affiche 1 2 4 au lieu de 1 2 3 4  donc remove elem courant bien pris en compte
  while(!list_iterator_end(it)){
    if(it->current->b==5){
      supprimerElementCourant(it);
    }
    poids= it->current->poids;
    printf("%d\n",poids);
    it= list_iterator_next(it);
  }

l=decreaseSort(l);
for(LinkedElement *e=l->sentinel->next; e!=l->sentinel; e=e->next){
    printf("%d ", e->poids);
  }
  printf("\n");





  ListIterator = list_iterator_create(l,FORWARD_ITERATOR);
  for (Element e = list_iterator_next(l);list_iterator_end(it); e = list_iterator_next())
  {
    /* code */
  }
  
return 0;
}