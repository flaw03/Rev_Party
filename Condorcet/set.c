
/*-----------------------------------------------------------------*/
/*
 Implantation du TAD List .
 */
/*-----------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "set.h"


struct s_disjointSet {
    int size;
    int *parent;
    int *rank;
};

// Initialiser un ensemble disjoint
DisjointSet *createDisjointSet(int n) {
    DisjointSet *set = malloc(sizeof(DisjointSet));
    set->parent = malloc(n * sizeof(int));
    set->rank = malloc(n * sizeof(int));
    set->size = n;
    for (int i = 0; i < n; i++) {
        set->parent[i] = -1;
        set->rank[i] = 0;
    }
    return set;
}

// Libérer la mémoire d'un ensemble disjoint
void freeDisjointSet(DisjointSet *set) {
    free(set->parent);
    free(set->rank);
    free(set);
}

// Trouver la racine de l'ensemble
int find(DisjointSet *set, int i) {
    if (set->parent[i] == -1)
        return i;
    return find(set, set->parent[i]);
}

// Fusionner deux ensembles disjoints par leurs représentants
void unionSets(DisjointSet *set, int x, int y) {

    int rootX = find(set, x);
    int rootY = find(set, y);

    // Fusionner par rang pour maintenir l'équilibre de l'arbre
    if (set->rank[rootX] < set->rank[rootY])
        set->parent[rootX] = rootY;
    else if (set->rank[rootX] > set->rank[rootY])
        set->parent[rootY] = rootX;
    else {
        set->parent[rootX] = rootY;
        set->rank[rootY]++;
    }
}

// Vérifier si l'ajout de l'arête (u, v) créerait un cycle
int doesCreateCycle(DisjointSet *set, int u, int v) {
    int rootU = find(set, u);
    int rootV = find(set, v);

    // Si les représentants sont les mêmes, il y aurait un cycle
    return (rootU == rootV);
}

int rootThree(DisjointSet *set){
    for (int i = 0;set->parent[i] != -1;i++)
    return i;
}
