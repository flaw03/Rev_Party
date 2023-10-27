#include <stdio.h>
#include <stdlib.h>

int* create_tab1D(int nb_colonne){
  int* tab;
  tab=malloc(nb_colonne*sizeof(int));
  return tab;
}

int** create_tab2D(int nb_ligne, int nb_colonne){
  int** tab=malloc(nb_ligne*sizeof(int));
  for(int i=0; i<nb_ligne;i++){
    tab[i]= malloc(nb_colonne*sizeof(int));
  }
  return tab;
}

void delete_tab1D(int* tableau){
  free(tableau);
}

void deleteTableau2D(int** tableau, int nb_ligne) {
    for (int i = 0; i < nb_ligne; i++) {
        free(tableau[i]);
    }
    free(tableau);
}

int main() {
  //Test tab
  int* tab1d;
  int** tab2d;
  tab1d=create_tab1D(3);
  tab2d=create_tab2D(3,3);
  printf("mat1d : ");
  for (int i=0;i<3;i++){
    printf("%d ",tab1d[i]);
  }

  printf("\nmat2d : ");

  for (int i=0;i<3;i++){
    printf("\n      ");
    for(int j=0; j<3;j++){
      printf("%d",tab2d[i][j]);
    }
  }
delete_tab1D(tab1d);
deleteTableau2D(tab2d,3);
printf("\n");
  return 0;
}
