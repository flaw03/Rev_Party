#ifndef __SET_H__
#define __SET_H__

#include <stdbool.h>
#include "list.h"


// Structure pour représenter un ensemble disjoint
typedef struct s_disjointSet DisjointSet;

// Initialiser un ensemble disjoint
DisjointSet * createDisjointSet(int n);

// Libérer la mémoire d'un ensemble disjoint
void freeDisjointSet(DisjointSet *set);

// Fusionner deux ensembles disjoints par leurs représentants
void addEdge(DisjointSet *set, int x, int y) ;

// Vérifier si l'ajout de l'arête (u, v) créerait un cycle
int doesCreateCycle(DisjointSet *set, int u, int v);

// Trouver la racine de l'ensemble
int findRoot(DisjointSet *set);

// Afficher la matrice de l'ensemble disjoint
void printSet(DisjointSet *set,FILE * logfile);


#endif

