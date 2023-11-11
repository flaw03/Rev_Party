#include "utils_tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


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
	matrice->nb_colonne = nb_colonne;
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

void afficher_Matrice(Matrice matrice){
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
            matrice->tableau[j][i] = valeur;
        }
    }
}

/**
 * @brief Trouve le minimum dans une matrice.
 *
 * Cette fonction recherche le minimum dans une matrice et retourne ses coordonnées
 * (ligne et colonne) ainsi que sa valeur. Si aucun minimum n'est trouvé, la valeur est
 * mise à jour à -1.
 *
 * @param matrice La matrice dans laquelle rechercher le minimum.
 * @param ligne Variable pour stocker la ligne du minimum.
 * @param colonne Variable pour stocker la colonne du minimum.
 * @param valeur Variable pour stocker la valeur minimale.
 */
void min_Matrice(Matrice matrice, int *ligne, int *colonne, int *valeur) {
    // Initialisation des valeurs minimales avec des valeurs arbitraires
    *valeur = INT_MAX;  // Utilisation de INT_MAX de <limits.h> pour une valeur initiale maximale
    *ligne = -1;        // Initialisation avec une valeur non valide
    *colonne = -1;      // Initialisation avec une valeur non valide

    // Parcours de la matrice pour trouver le minimum
    for (int i = 0; i < matrice->nb_ligne; i++) {
        for (int j = 0; j < matrice->nb_colonne; j++) {
            int element = matrice->tableau[i][j];

            // Vérification si l'élément est un candidat pour être le minimum
            if (element > 0 && element < *valeur) {
                // Mise à jour des valeurs minimales
                *valeur = element;
                *ligne = i;
                *colonne = j;
            }
        }
    }

    // Si aucun minimum n'a été trouvé, la valeur minimale est définie sur -1
    if (*valeur == INT_MAX) {
        *valeur = -1;
    }
}


/**
 * @brief Remplit la matrice en duel en fonction des valeurs de matriceLigne.
 *
 * @param matrice La matrice à remplir.
 * @param matriceLigne La matrice contenant les valeurs à utiliser.
 */
void remplire_Matrice_Duel(Matrice matrice, Matrice matriceLigne) {
    int colonne;
    int ligne;
    int valeur;

    // Trouver le minimum dans matriceLigne
    min_Matrice(matriceLigne, &ligne, &colonne, &valeur);

    // Tant qu'il y a des valeurs à traiter dans matriceLigne
    while (valeur != -1) {
        // Marquer la valeur comme traitée
        matriceLigne->tableau[ligne][colonne] = -1;

        // Parcourir les lignes de matrice
        for (int i = 0; i < matrice->nb_ligne; i++) {
            // Vérifier si la valeur n'est pas déjà marquée comme traitée
            if (matriceLigne->tableau[0][i] != -1) {
                // Vérifier si la valeur dans matriceLigne correspond à la valeur trouvée précédemment
                if (matriceLigne->tableau[0][i] == valeur) {
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
        min_Matrice(matriceLigne, &ligne, &colonne, &valeur);
    }
}