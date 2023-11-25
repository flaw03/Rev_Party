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

  //affiche 1 2 4 au lieu de 1 2 3 4  donc remove elem courant bien pris en compte
  
  /*while(!list_iterator_end(it)){
    if(it->current->b==5){
      supprimerElementCourant(it);
    }
    poids= it->current->element->p;
    printf("%d\n",poids);
    it= list_iterator_next(it);
  }*/

int i=decreaseSort(l);
printf("%d\n",list_size(l));
printf("retour triee %d\n",i);

/*
J'ai ete oblige de tester la fonction triee dans le fichier liste avec (for LinkedElement* e...) voir code en-dessous car ta modification sur l'iterateur de la fonction next 
ne permet pas d'iterer correctement donc a toi de corriger soit en revenant a la version que j'avais donne au depart ou de trouver
une autre solution

Le module est sans fuite.
*/
  for (LinkedElement *e = l->sentinel->next ; e!=l->sentinel; e=e->next)
  {
    printf("%d ", e->element->p);
  }
  printf("\n");
  
  list_delete(&l);
return 0;
}
