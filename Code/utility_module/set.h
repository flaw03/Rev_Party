/*-----------------------------------------------------------------*/
/*
 Interface pour l'implémentation du TAD Set pour le projet.
 */
/*-----------------------------------------------------------------*/

#ifndef __SET_H__
#define __SET_H__

#include <stdbool.h>
#include "list.h"

/** \defgroup ADTSet Set
 Documentation de l'implémentation du type abstrait de données Set (Ensemble).
 @{
 */

/** \defgroup TypeSet Définition du type.
  @{
 */
/** Définition opaque du type DisjointSet (Ensemble Disjoint).
 */
typedef struct s_disjointSet DisjointSet;
/** @} */

/*-----------------------------------------------------------------*/

/** \defgroup Constructeurs Constructeurs et destructeurs du TAD.
 @{
 */
/** Constructeur pour créer un ensemble disjoint.
 	@param n La taille de l'ensemble.
 	@return Un pointeur vers l'ensemble disjoint nouvellement créé.
 */
DisjointSet *createDisjointSet(int n);

/** Destructeur pour libérer la mémoire allouée à un ensemble disjoint.
	@param set L'ensemble disjoint à libérer.
 */
void freeDisjointSet(DisjointSet *set);
/** @} */

/*-----------------------------------------------------------------*/

/** \defgroup OpérationsSurEnsemble Opérations sur les ensembles.
 @{
 */
/** Ajoute une arête entre les ensembles qui contiennent les éléments x et y.
	@param set L'ensemble disjoint.
	@param x Élément x.
	@param y Élément y.
 */
void addEdge(DisjointSet *set, int x, int y);

/** Vérifie si l'ajout d'une arête entre les ensembles contenant u et v crée un cycle.
	@param set L'ensemble disjoint.
	@param u Élément u.
	@param v Élément v.
	@return true si l'ajout de l'arête crée un cycle, sinon false.
 */
int doesCreateCycle(DisjointSet *set, int u, int v);

/** Trouve la racine (ensemble parent) d'un élément dans l'ensemble disjoint.
	@param set L'ensemble disjoint.
	@return La racine de l'élément.
 */
int findRoot(DisjointSet *set);

/** Affiche l'ensemble disjoint dans un fichier journal.
	@param set L'ensemble disjoint.
	@param logfile Pointeur vers le fichier journal où afficher l'ensemble disjoint.
 */
void printSet(DisjointSet *set, FILE *logfile);
/** @} */

/** @} */

#endif
