
#ifndef __LECTURE_CSV_H__
#define __LECTURE_CSV_H__

#include "utils_tab.h"

#define MAX_LIGNES 1024
#define MAX_COLONNES 1024
#define MAX_LINE_LENGTH 1024
#define MARGE 4
#define COLONNE_SHA 3
#define BUFFER_SIZE 16


void isCSV(const char* filename);

char * obtenir_nom_Candidat(const char *filename,int numColonne);

void afficher_vote(const char* filename,char* hash);

int lireCSVCondorcet(char* filename,Matrice *Matrice);

#endif
