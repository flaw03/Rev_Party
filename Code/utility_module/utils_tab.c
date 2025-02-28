#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "utils_tab.h"



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


void afficher_Matrice(Matrice matrice,FILE* logfile){
	fprintf(logfile,"I/I|");
	for(int j = 0; j <  matrice->nb_colonne;j++){
		fprintf(logfile,"%-4d|",j);
	}
	fprintf(logfile,"\n");
	for(int j = 0; j < ( matrice->nb_colonne + 1) * 5;j++){
		fprintf(logfile,"-");
		}
	fprintf(logfile,"\n");
	for(int i = 0 ; i < matrice->nb_ligne;i++){
		fprintf(logfile,"%-3d|",i);
		for (int j = 0; j < matrice->nb_colonne;j++){
		fprintf(logfile,"%-4d|",matrice->tableau[i][j]);
		}
		fprintf(logfile,"\n");
		for(int j = 0; j <  (matrice->nb_colonne + 1) * 5;j++){
		fprintf(logfile,"-");
		}
		fprintf(logfile,"\n");
	}
}

void afficherVote(Tableau tab,FILE* logfile){
    fprintf(logfile,"[");
    for(int i = 0;i<tab->dim-1;i++){
        fprintf(logfile,"%d-",tab->tableau[i]);
        
    }
    fprintf(logfile,"%d]",tab->tableau[tab->dim-1]);

}


void afficher_Tableau(Tableau tab,FILE* logfile){
    for(int j = 0; j < tab->dim;j++){
		fprintf(logfile,"%-4d|",j);
	}
     fprintf(logfile,"\n");;
    for(int j = 0; j < (tab->dim) * 5;j++){
		fprintf(logfile,"-");
		}
     fprintf(logfile,"\n");
	for(int i = 0; i <  tab->dim;i++){
		fprintf(logfile,"%-4d|",tab->tableau[i]);
	}
     fprintf(logfile,"\n");
    for(int j = 0; j < (tab->dim) * 5;j++){
		fprintf(logfile,"-");
		}
    fprintf(logfile,"\n");
}


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
        if (element >= 0 && element < *valeur) {
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

void trier_Tableau(Tableau tab) {
    for (int i = 0; i < tab->dim; i++) {
        for (int j = 0; j < tab->dim; j++) {
            if (tab->tableau[i] > tab->tableau[j]) {
                int temp = tab->tableau[i];
                tab->tableau[i] = tab->tableau[j];
                tab->tableau[j] = temp;
            }
        }
    }
}


