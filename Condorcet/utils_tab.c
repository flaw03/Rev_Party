#include "utils_tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>



Tableau create_Tableau(int dim){
	Tableau tab = malloc(sizeof(struct t_Tableau));
    tab->dim = dim;
    tab->tableau = malloc(dim * sizeof(int));
	return tab;
}


Matrice create_Matrice(int nb_ligne, int nb_colonne){
	Matrice matrice = malloc(sizeof(struct t_Matrice));
	matrice->nb_colonne = nb_colonne;
	matrice->nb_ligne = nb_ligne;
	matrice->tableau = malloc(nb_ligne * sizeof(int *));
    for(int i=0; i< nb_ligne;i++){
		matrice->tableau[i] = malloc(nb_colonne*sizeof(int));
	}
	return matrice;
}

void delete_Matrice(Matrice matrice){
    for (int i = 0; i < matrice->nb_ligne; i++) {
        free(matrice->tableau[i]);
    }
    free(matrice->tableau);
    free(matrice);
}


void delete_Tableau(Tableau tab){
    free(tab->tableau);
    free(tab);
}


void afficher_Matrice(Matrice matrice){
    printf("\nAfficher la matrice %d %d\n",matrice->nb_ligne,matrice->nb_ligne);
	printf("I/I|");
	for(int j = 0; j <  matrice->nb_colonne;j++){
		printf("%-4d|",j);
	}
	printf("\n");
	for(int j = 0; j < ( matrice->nb_colonne + 1) * 5;j++){
		printf("-");
		}
	printf("\n");
	for(int i = 0 ; i < matrice->nb_ligne;i++){
		printf("%-3d|",i);
		for (int j = 0; j < matrice->nb_colonne;j++){
		printf("%-4d|",matrice->tableau[i][j]);
		}
		printf("\n");
		for(int j = 0; j <  (matrice->nb_colonne + 1) * 5;j++){
		printf("-");
		}
		printf("\n");
	}
}


void afficher_Tableau(Tableau tab){
    printf("\nAfficher le tableau %d\n",tab->dim);
    for(int j = 0; j < tab->dim;j++){
		printf("%-4d|",j);
	}
     printf("\n");;
    for(int j = 0; j < (tab->dim) * 5;j++){
		printf("-");
		}
     printf("\n");
	for(int i = 0; i <  tab->dim;i++){
		printf("%-4d|",tab->tableau[i]);
	}
     printf("\n");
    for(int j = 0; j < (tab->dim) * 5;j++){
		printf("-");
		}
    printf("\n");
}

/**
 * @brief Initialise une matrice avec une valeur spécifique.
 *
 * Cette fonction initialise tous les éléments d'une matrice avec une valeur spécifique.
 *
 * @param matrice La matrice à initialiser.
 * @param valeur La valeur avec laquelle initialiser la matrice.
 */
void init_Matrice(Matrice matrice, int valeur) {
    // Parcours de la matrice pour initialiser chaque élément avec la valeur spécifiée
    for (int i = 0; i < matrice->nb_ligne; i++) {
        for (int j = 0; j < matrice->nb_colonne; j++) {
            matrice->tableau[i][j] = valeur;
        }
    }
}

void init_Tableau(Tableau tab,int valeur){
    for(int i = 0; i<tab->dim;i++){
        tab->tableau[i] = valeur;
    }
}

int min_Tableau(Tableau tab,int *colonne, int *valeur) {
    // Initialisation des valeurs minimales avec des valeurs arbitraires
    int doublon = 0;    // Initialisation avec une valeur non valide
    *valeur = INT_MAX;  // Utilisation de INT_MAX de <limits.h> pour une valeur initiale maximale
    *colonne = -1;      // Initialisation avec une valeur non valide

    // Parcours de la matrice pour trouver le minimum
    for (int i = 0; i < tab->dim; i++) {
        int element = tab->tableau[i];

        // Vérification si l'élément est un candidat pour être le minimum
        if (element > 0 && element < *valeur) {
            // Mise à jour des valeurs minimales
            doublon = 0;
            *valeur = element;
            *colonne = i;
        }
        else if (element == *valeur){
            doublon = 1;
        }   
    }
    // Si aucun minimum n'a été trouvé, la valeur minimale est définie sur -1
    if (*valeur == INT_MAX) {
        *valeur = -1;
    }
    return doublon;
}


int max_Tableau(Tableau tab, int *colonne,int * valeur){
    // Initialisation des valeurs minimales avec des valeurs arbitraires
    int doublon = 0;    // Initialisation avec une valeur non valide
    *valeur = INT_MIN;  // Utilisation de INT_MAX de <limits.h> pour une valeur initiale maximale
    *colonne = -1;      // Initialisation avec une valeur non valide

    // Parcours de la matrice pour trouver le minimum
    for (int i = 0; i < tab->dim; i++) {
        int element = tab->tableau[i];
        // Vérification si l'élément est un candidat pour être le minimum
        if (element > *valeur) {
            // Mise à jour des valeurs minimales
            doublon = 0;
            *valeur = element;
            *colonne = i;
        }
        else if (element == *valeur){
            doublon = 1;
        }   
    }
    // Si aucun minimum n'a été trouvé, la valeur minimale est définie sur -1
    return doublon;
}



void remplire_Matrice_Duel(Matrice matrice, Tableau tab) {
    int colonne;
    int valeur;
    // Trouver le minimum dans le tableau
    min_Tableau(tab, &colonne, &valeur);

    // Tant qu'il y a des valeurs à traiter dans matriceLigne
    while (valeur != -1) {
        // Marquer la valeur comme traitée
        tab->tableau[colonne] = -1;
        // Parcourir les lignes de matrice
        for (int i = 0; i < matrice->nb_ligne; i++) {
            // Vérifier si la valeur n'est pas déjà marquée comme traitée
            if (tab->tableau[i] != -1) {
                // Vérifier si la valeur dans matriceLigne correspond à la valeur trouvée précédemment
                if (tab->tableau[i] == valeur) {
                    // Incrémenter les valeurs correspondantes dans matrice
                    matrice->tableau[colonne][i]++;
                    matrice->tableau[i][colonne]++;
                } else {
                    // Si la valeur ne correspond pas, incrémenter seulement la valeur dans la colonne correspondante de matrice
                    matrice->tableau[colonne][i]++;
                }
            }
        }
        
        // Trouver le prochain minimum dans matriceLigne
        min_Tableau(tab, &colonne, &valeur);
    }
}

