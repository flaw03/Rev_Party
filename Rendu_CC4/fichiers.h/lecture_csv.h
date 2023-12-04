
#ifndef __LECTURE_CSV_H__
#define __LECTURE_CSV_H__

#include "utils_tab.h"
#include "stdbool.h"




char * obtenir_nom_Candidat(const char *filename,int numColonne,bool isBallot);

void afficher_vote(const char* filename,char* hash);

int lireBallot(char* filename,Matrice *Matrice);

int lireMatriceDuel(char* filename,Matrice *Matrice);


#endif
