/*
	*Implantation de la structure Matrice
*/

#ifndef __UTILS_TAB_H__
#define __UTILS_TAB_H__

/*
 *Opaque definiton of type Matrice
 */
typedef struct t_Matrice *Matrice;

/*
 *Implementation of the constructor 
 @param nb_ligne number of line in the matrix
 @param nb_colonne number of column in the matrix
 @return the allocated matrix
*/
Matrice create_Matrice(int nb_ligne, int nb_colonne);

/** Destructor.
	Added by the implementation. Free ressources allocated by constructors.
 	@param matrice the matrix.
 	After calling this function, the matrix matrice becomes NULL.
 */
void delete_Matrice(Matrice matrice);


#endif