#ifndef __UTILS_TAB_H__
#define __UTILS_TAB_H__
#include <stdio.h>


/**
 * @brief Structure représentant une matrice d'entiers.
 */
typedef struct t_Matrice {
  int nb_ligne;    /**< Nombre de lignes de la matrice. */
  int nb_colonne;  /**< Nombre de colonnes de la matrice. */
  int **tableau;   /**< Tableau d'entiers représentant la matrice. */
}* Matrice;

/**
 * @brief Structure représentant un tableau d'entiers.
 */
typedef struct t_Tableau {
  int dim;         /**< Dimension du tableau. */
  int *tableau;    /**< Tableau d'entiers. */
} * Tableau;

/**
 * @brief Crée une nouvelle matrice d'entiers.
 * 
 * @param nb_ligne Nombre de lignes de la matrice.
 * @param nb_colonne Nombre de colonnes de la matrice.
 * @return Pointeur vers la nouvelle matrice.
 */
Matrice create_Matrice(int nb_ligne, int nb_colonne);

/**
 * @brief Libère la mémoire allouée pour une matrice.
 *
 * @param matrice La matrice à libérer.
 */
void delete_Matrice(Matrice matrice);

/**
 * @brief Initialise les valeurs d'une matrice avec une valeur donnée.
 *
 * @param matrice La matrice à initialiser.
 * @param valeur La valeur avec laquelle initialiser la matrice.
 */
void init_Matrice(Matrice matrice, int valeur);

/**
 * @brief Crée un nouveau tableau d'entiers.
 *
 * @param dim Dimension du tableau.
 * @return Pointeur vers le nouveau tableau.
 */
Tableau create_Tableau(int dim);

/**
 * @brief Libère la mémoire allouée pour un tableau.
 *
 * @param Tableau Le tableau à libérer.
 */
void delete_Tableau(Tableau Tableau);

/**
 * @brief Initialise les valeurs d'un tableau avec une valeur donnée.
 *
 * @param tab Le tableau à initialiser.
 * @param valeur La valeur avec laquelle initialiser le tableau.
 */
void init_Tableau(Tableau tab, int valeur);

/**
 * @brief Trouve le minimum dans un tableau et retourne ses coordonnées et sa valeur.
 *
 * Cette fonction recherche le minimum dans un tableau en considérant uniquement les
 * éléments supérieurs ou égaux à zéro. Elle retourne les coordonnées (colonne) et la
 * valeur du minimum trouvé. Si aucun minimum n'est trouvé, la valeur est mise à jour à -1.
 *
 * @param tab Le tableau dans lequel rechercher le minimum.
 * @param colonne Variable pour stocker la colonne du minimum.
 * @param valeur Variable pour stocker la valeur minimale.
 * @return Nombre d'éléments supérieurs à la valeur minimale.
 */
int min_Tableau(Tableau tab, int *colonne, int *valeur);

/**
 * @brief Trouve le maximum dans un tableau et retourne ses coordonnées et sa valeur.
 *
 * @param tab Le tableau dans lequel rechercher le maximum.
 * @param colonne Variable pour stocker la colonne du maximum.
 * @param valeur Variable pour stocker la valeur maximale.
 * @return Nombre d'éléments supérieurs à la valeur maximale.
 */
int max_Tableau(Tableau tab, int *colonne, int *valeur);

/**
 * @brief Remplit la matrice de duel en fonction des valeurs du tableau.
 *
 * @param matrice La matrice à remplir.
 * @param tableau Le tableau contenant les valeurs à utiliser.
 */
void remplire_Matrice_Duel(Matrice matrice, Tableau tableau);

/**
 * @brief Affiche la matrice dans un fichier journal.
 *
 * @param matrice La matrice à afficher.
 * @param logfile Pointeur vers le fichier journal.
 */
void afficher_Matrice(Matrice matrice, FILE *logfile);

/**
 * @brief Affiche le tableau dans un fichier journal.
 *
 * @param Tableau Le tableau à afficher.
 * @param logfile Pointeur vers le fichier journal.
 */
void afficher_Tableau(Tableau Tableau, FILE *logfile);

/**
* @brief Fonction : trier
* @brief Description : Trie un tableau par ordre décroissant.
* @param tab : Le tableau à trier.
*/
void trier_Tableau(Tableau tableau);




#endif
