#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"
int main(void)
{
  List* l=list_create();
  l=list_push_back(l,1,"aa","bb");
  l=list_push_back(l,1,"aa","bb");
  l=list_push_back(l,1,"aa","bb");
  printf("size %d\n", list_size(l));
  list_at(l,2);
  l=list_pop_back(l);
  printf("size %d\n", list_size(l));
  return 0;
}
