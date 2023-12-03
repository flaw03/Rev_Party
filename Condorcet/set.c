
/*-----------------------------------------------------------------*/
/*
 Implantation du TAD List .
 */
/*-----------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "utils_tab.h"


struct s_disjointSet {
    Matrice matrice;
};

// Initialiser un ensemble disjoint
DisjointSet *createDisjointSet(int n) {
    DisjointSet *set = malloc(sizeof(DisjointSet));
    set->matrice = create_Matrice(n,n);
    init_Matrice(set->matrice,0);
    return set;
}

// Libérer la mémoire d'un ensemble disjoint
void freeDisjointSet(DisjointSet *set) {
    delete_Matrice(set->matrice);
    free(set);
}


// Fusionner deux ensembles disjoints par leurs représentants
void addEdge(DisjointSet *set, int x, int y) {
    set->matrice->tableau[x][y] = 1;
}
// Vérifier si l'ajout de l'arête (u, v) créerait un cycle
int doesCreateCycle(DisjointSet *set, int x, int y) {
    if (set->matrice->tableau[y][x] == 1){
        return 1;
    }
    for(int i = 0; i < set->matrice->nb_colonne; i++){
        if (set->matrice->tableau[y][i] == 1 && doesCreateCycle(set, x, i) == 1){
            return 1;
        }
    }
    return 0;
}

void printSet(DisjointSet *set){
    afficher_Matrice(set->matrice);
}

int rootThree(DisjointSet *set){
    int i,j;
    int fin = 0;
    for (i = 0; i < set->matrice->nb_colonne && !fin;i++){
        for (j = 0;j < set->matrice->nb_colonne && !set->matrice->tableau[j][i];j++);
        if (j == set->matrice->nb_colonne){
            return i;
        }
    }
    return -1;
}



