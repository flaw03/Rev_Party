#ifndef __SET_H__
#define __SET_H__

#include <stdbool.h>
#include "list.h"

/** 
 * @defgroup TADSet Set
 * @brief Documentation of the Set type and operators
 *@{
 */

/** 
 * @brief Opaque definition of the DijointSet abstract data type.
 */
typedef struct s_disjointSet DisjointSet;

/**
 * @brief Constructor of an empty DisjointSet.
 * 
 * @par Profile
 * @parblock
 * createDisjointSet : -> DisjointSet.
 * @endparblock
 * @param n size of a square matrix.
 * @return a correctly initialized DisjointSet.
 */ 
DisjointSet * createDisjointSet(int n);

/**
 * @brief Destructor of a DisjointSet.
 * 
 * @par Profile
 * @parblock
 * freeDisjointSet : DisjointSet -> void.
 * @endparblock 
 * @param The DisjointSet to delete.
 */
void freeDisjointSet(DisjointSet *set);

/**
 * @brief Merging two DisjointSet by their representatives.
 * @par Profile
 * @parblock
 * addEdge : DisjointSet -> int -> int -> void.
 * @endparblock
 * @param set address of the DisjointSet resulting from the union of the two DisjointSet.
 * @param x representative of the first DisjointSet.
 * @param y representative of the second DisjointSet.
*/
void addEdge(DisjointSet *set, int x, int y) ;

/**
 * @brief Check whether adding the edge (u, v) would create a cycle.
 * @par Profile
 * @parblock
 * doesCreateCycle : DisjointSet -> int -> int -> int.
 * @endparblock
 * @param set The DisjointSet to check if the adding edge would create a cycle.
 * @param u Origin of the edge.
 * @param y The end of the edge.
 * @return whether or not the addition creates a cycle.
*/
int doesCreateCycle(DisjointSet *set, int u, int v);

/**
 * @brief Fin the root of the DisjointSet.
 * @par Profile
 * @parblock
 * findRoot : DisjointSet -> int.
 * @endparblock
 * @param set DisjointSet whose root has to be found.
 * @return The root of the DisjointSet or -1.
*/
int findRoot(DisjointSet *set);

/**
 * @brief Print the matrix of the DisjointSet.
 * @par Profil
 * @parblock
 * doesCreateCycle : DisjointSet -> FILE -> void.
 * @endparblock
 * @param set The DisjointSet to print .
 * @param logfile The file to display the matrix.
*/
void printSet(DisjointSet *set,FILE * logfile);

/** @} */

/** @} */

#endif

