#include "utils_tab.h"
#include <stdio.h>
#include <stdlib.h>


Colonne create_tab1D(int nb_colonne){
  int* tab;
  tab = malloc(nb_colonne*sizeof(int));
  return tab;
}

Tableau create_tab2D(int nb_ligne, int nb_colonne){
  Tableau tab = malloc(nb_ligne * sizeof(int *));
  for(int i=0; i<nb_ligne;i++){
    tab[i]= malloc(nb_colonne*sizeof(int));
  }
  return tab;
}

Matrice create_Matrice(int nb_ligne, int nb_colonne){
  Matrice matrice = malloc(sizeof(struct t_Matrice));
  matrice->nb_colone = nb_colonne;
  matrice->nb_ligne = nb_ligne;
  matrice->tableau = create_tab2D(nb_ligne,nb_colonne);
  return matrice;
}

void delete_colone(Colonne colone){
  free(colone);
}

void deleteTableau(Tableau tableau,int nb_ligne) {
    for (int i = 0; i < nb_ligne; i++) {
        delete_colone(tableau[i]);
    }
    free(tableau);
}

void delete_Matrice(Matrice matrice){
    deleteTableau (matrice->tableau,matrice->nb_ligne);
    free(matrice);
}


void init_Matrice(Matrice matrice,int valeur){
  for(int i = 0 ; i < matrice->nb_ligne;i++){
    for (int j = 0; j < matrice->nb_colone;j++){
      matrice->tableau[j][i] = valeur;
    } 
  }
}

void afficher_Matrice(Matrice matrice){
  for(int i = 0 ; i < matrice->nb_ligne;i++){
    for (int j = 0; j < matrice->nb_colone;j++){
      printf("%d ",matrice->tableau[i][j]);
    }
    printf("\n");
  }
}
