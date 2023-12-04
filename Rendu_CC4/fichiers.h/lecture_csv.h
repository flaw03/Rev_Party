
#ifndef __LECTURE_CSV_H__
#define __LECTURE_CSV_H__

#include "utils_tab.h"
#include "stdbool.h"



/**
 * @brief Get a candidate's name.
 * @param filename The name of the file.
 * @param numColonne The number of the column.
 * @param isBallot Whether it's a ballot or not.
 * @retrurn The name of the candidate.
*/
char * obtenir_nom_Candidat(const char *filename,int numColonne,bool isBallot);


/**
 * @brief Print the vote of an elector.
 * @param filename The name of the file.
 * @param hash The hashcode of thde elector.
*/
void afficher_vote(const char* filename,char* hash);

/**
 * @brief Read a ballot of vote.
 * @param filename The name of the file.
 * @param Matrice matrix to store the reading data.
 * @retrurn The number of elector.
*/
int lireBallot(char* filename,Matrice *Matrice);

/**
 * @brief Read a duel matrix.
 * @param filename The name of the file.
 * @param Matrice matrix to store the reading data.
 * @retrurn The number of reading line.
*/
int lireMatriceDuel(char* filename,Matrice *Matrice);


#endif
