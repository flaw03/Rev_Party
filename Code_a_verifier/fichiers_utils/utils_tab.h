#ifndef __UTILS_TAB_H__
#define __UTILS_TAB_H__


typedef struct t_Matrice *Matrice;


Matrice create_Matrice(int nb_ligne, int nb_colonne);

void delete_Matrice(Matrice matrice);


#endif