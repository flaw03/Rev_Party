#ifndef __UTILS_TAB_H__
#define __UTILS_TAB_H__

typedef int* Colonne;
typedef Colonne * Tableau;

struct t_Matrice {
  int nb_ligne;
  int nb_colonne;
  Tableau tableau;
};

typedef struct t_Matrice *Matrice;


Matrice create_Matrice(int nb_ligne, int nb_colonne);

void delete_Matrice(Matrice matrice);

void init_Matrice(Matrice matrice,int valeur);


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
void min_Matrice(Matrice matrice, int * ligne , int * colonne , int * valeur);


/**
 * @brief Trouve le maximun dans une matrice et renvoie le nombre d'elment superieur;
 *
 * Cette fonction recherche le minimum dans une matrice et retourne ses coordonnées
 * (ligne et colonne) ainsi que sa valeur. Si aucun minimum n'est trouvé, la valeur est
 * mise à jour à -1.
 *
 * @param matrice La matrice dans laquelle rechercher le minimum.
 * @param colonne Variable pour stocker la colonne du minimum.
 */
int max_Matrice_Ligne(Matrice matrice, int *colonne,int * valeur); 


/**
 * @brief Remplit la matrice en duel en fonction des valeurs de matriceLigne.
 *
 * @param matrice La matrice à remplir.
 * @param matriceLigne La matrice contenant les valeurs à utiliser.
 */
void remplire_Matrice_Duel(Matrice matrice,Matrice ligne);


void afficher_Matrice(Matrice matrice);

Matrice obtenirPiresScores(Matrice matriceCombat);

#endif
