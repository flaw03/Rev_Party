
#ifndef __LECTURE_CSV_H__
#define __LECTURE_CSV_H__

#include "utils_tab.h"



// Vérifie si le fichier a l'extension ".csv"
int fichierEstCSV(const char* filename);

// Obtient le nom du candidat dans la colonne spécifiée du fichier CSV
char *obtenirNomCandidat(const char *filename, int numColonne);

// Affiche le vote associé à un hachage dans le fichier CSV
void afficherVote(const char* filename, char* hash);

// Lit un fichier de bulletins de vote et initialise une matrice de duel renvoie le nombre d'electeur
int lireBallot(char* filename,Matrice *Matrice);

// Lit un fichier de matrice de duel et initialise une matrice correspondante renvoie le nombre d'electeur 
int lireMatriceDuel(char* filename, Matrice *matrice);


#endif
