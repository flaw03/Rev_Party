#ifndef __UTILS_TAB_H__
#define __UTILS_TAB_H__
#include <stdio.h>


typedef struct t_Matrice *Matrice;
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
 * @brief Trouve le minimum dans une matrice.
 *
 * Cette fonction recherche le minimum dans une matrice et retourne ses coordonnées
 * (ligne et colonne) ainsi que sa valeur. Si aucun minimum n'est trouvé, la valeur est
 * mise à jour à -1.
 *
 * @param matrice La matrice dans laquelle rechercher le minimum.
 * @param colonne Variable pour stocker la colonne du minimum.
 * @param valeur Variable pour stocker la valeur minimale.
 */
int min_Tableau(Tableau tab, int * colonne , int * valeur);


/**
 * @brief Trouve le maximun dans une matrice et renvoie le nombre d'elment superieur;
 *
 * Cette fonction recherche le minimum dans une matrice et retourne ses coordonnées
 * (ligne et colonne) ainsi que sa valeur. Si aucun minimum n'est trouvé, la valeur est
 * mise à jour à -1.
 *
 * @param Tableau La matrice dans laquelle rechercher le minimum.
 * @param colonne Variable pour stocker la colonne du minimum.
 */
int max_Tableau(Tableau tab, int *colonne,int * valeur); 


/**
 * @brief Remplit la matrice en duel en fonction des valeurs de matriceLigne.
 *
 * @param matrice La matrice à remplir.
 * @param tableau Le tableau contenant les valeurs à utiliser.
 */
void remplire_Matrice_Duel(Matrice matrice,Tableau Tableau);


void afficher_Matrice(Matrice matrice,FILE* logfile);

void afficher_Tableau(Tableau Tableau,FILE* logfile);

#endif
