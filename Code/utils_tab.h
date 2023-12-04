#ifndef __UTILS_TAB_H__
#define __UTILS_TAB_H__
#include <stdio.h>

/** 
 * @defgroup Utils Utils 
 * @brief Documentation of utils functions for the project.
 *@{
 */

/** 
 * @brief Opaque definition of Matrice abstract data type.
 */
typedef struct t_Matrice *Matrice;

/** 
 * @brief Opaque definition of Tableau abstract data type.
 */
typedef struct t_Tableau *Tableau;


struct t_Matrice {
  int nb_ligne;
  int nb_colonne;
  int ** tableau;
};


struct t_Tableau {
  int dim;
  int * tableau;
};


Matrice create_Matrice(int nb_ligne, int nb_colonne);
void delete_Matrice(Matrice matrice);
void init_Matrice(Matrice matrice,int valeur);





Tableau create_Tableau(int dim);
void delete_Tableau(Tableau Tableau);
void init_Tableau(Tableau tab,int valeur);


/**
 * @brief Find the minimum value in a matrix.
 *
 * @param matrice The matrix to find the minimum.
 * @param colonne Variable to store the column of the minimum value.
 * @param valeur Variable to store the minimum value.
 * @return The row and column of the minimum of the matrix, if no minimum is found, the value is updated to -1.
 */
int min_Tableau(Tableau tab, int * colonne , int * valeur);


/**
 * @brief Find the minimum value in a matrix.
 *
 * @param Tableau The matrix to find the maximum.
 * @param colonne Variable to store the column of the maximum value.
 * @param valeur Variable to store the maximum value.
 * @return The row and column of the maximum of the matrix, if no maximum is found, the value is updated to -1.
 */
int max_Tableau(Tableau tab, int *colonne,int * valeur); 


/**
 * @brief Fills the duel matrix.
 *
 * @param matrice The matrix to fill.
 * @param tableau The table of values to be used.
 */
void remplire_Matrice_Duel(Matrice matrice,Tableau Tableau);

/**
 * @brief Print the associated matrix.
 * @param matrice The matrix to print .
 * @param logfile The file to display the matrix.
*/
void afficher_Matrice(Matrice matrice,FILE* logfile);

/**
 * @brief Print the associated table.
 * @param Tableau The table to print .
 * @param logfile The file to display the matrix.
*/
void afficher_Tableau(Tableau Tableau,FILE* logfile);


/** @} */

/** @} */

#endif
