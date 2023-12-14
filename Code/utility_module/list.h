/*-----------------------------------------------------------------*/
/*
 
 Interface pour l'implantation du TAD List pour le projet.
 */
/*-----------------------------------------------------------------*/

#ifndef __LIST_H__
#define __LIST_H__

#include <stdbool.h>
#include "utils_tab.h"
/*-----------------------------------------------------------------*/

/** \defgroup ADTList List
 Documentation de l'implémentation du type abstrait de données List.
 @{
 */

/** \defgroup Type Type definition.
  @{
 */
/** Définition opaque du type List.
 */
typedef struct s_List List;
/** Définition du type ptrList : pointeur sur un TAD List.
 */
typedef List * ptrList;



typedef struct s_element{
	int a ;
	int b;
	int p;
} * Element;

/** @} */

/*-----------------------------------------------------------------*/

/** \defgroup Functors Prototypes des fonctions qui peuvent être utilisées avec certains opérateurs sur List.
 @{
 */
/** Foncteur simple à utiliser avec la fonction list_map.
 Ce foncteur reçoit en argument la valeur d'un élément de la liste et doit retourner éventuellement la valeur modifiée de l'élément.
 */
typedef int(*SimpleFunctor)(int,int,int);

/** Foncteur avec des données utilisateur à utiliser avec l'opérateur list_reduce.
  Ce foncteur reçoit en argument la valeur d'un élément de la liste et un pointeur opaque vers des données fournies par l'utilisateur, et doit retourner éventuellement la valeur modifiée de l'élément.
 */
typedef int (*ReduceFunctor)(Element,void *);

/** Foncteur à utiliser avec l'opérateur list_sort.
   Ce foncteur doit implémenter une fonction d'ordonnancement total (comp). Lorsque ce foncteur est appelé avec deux éléments de liste a et b, il doit renvoyer vrai si (a comp b).
 */
typedef bool(*OrderFunctor)(int, int);
/** @} */

/*-----------------------------------------------------------------*/

/** \defgroup Constructeurs.
 @{
 */
/** Implementation du constructor \c list.
 */
List *list_create(void);

/** Implementation du constructeur \c push_back.
 @param l La liste à modifier.
 @param p Le poids du candidat candidat1.
 @param candidat1 La valeur du candidat a.
 @param candidat2 TLa valeur du candidat b.
 @return La liste modifiée.
 */
List *list_push_back(List *l, int p, int candidat1, int candidat2);

/** Destructeur.
	@brief Libère les ressources allouées par les constructeurs. 
 	@param l L'adresse de la liste.
 */
void list_delete(ptrList *l);
/** @} */

/*-----------------------------------------------------------------*/

/** \defgroup FrontBackOperators Insertion et suppression d'éléments au début et à la fin de la liste.
 @{
 */
/** Ajoute un élément au début de la liste.
 	@param l La liste à modifer.
 	@param p Le poids du candidat candidat1.
 	@param candidat1 La valeur du candidat a.
 	@param candidat2 La valeur du candidat b.
 	@return La liste modifiée.
*/
List *list_push_front(List *l, int p, int candidat1, int candidat2);

/** Supprime un élément au début de la liste.
 	@return La liste modifiée.
 */
List *list_pop_front(List *l);

/** Supprime un élément à la fin de la liste.
 	@return La liste modifiée.
 */
List *list_pop_back(List *l);
/** @} */

/*-----------------------------------------------------------------*/

/** \defgroup Opérateurs d'accès Insertion et suppression d'éléments.
 @{
 */
/** Insérer un élément à la position donnée.
 	@param l La liste à modifier.
 	@param pos La position de l'élément à insérer.
 	@param p Le poids du candidat candidat1.
 	@param candidat1 La valeur du candidat a.
 	@param candidat2 La valeur du candidat b.
 	@return La liste modifiée.
 */
List *list_insert_at(List *l, int pos, int p, int candidat1,int candidat2);

/** Supprime l'élément à la position donnée.
	 @param l La liste à modifier.
	 @param p La position de l'élément à supprimer.
	 @return La liste modifiée.
 */
List *list_remove_at(List *l, int p);


/*-----------------------------------------------------------------*/

/** \defgroup OpérateursUtiles
 @{
 */
/** Vérifie si la liste est vide.
 */
bool list_is_empty(List *l);

/** Renvoie le nombre d'élements de la liste.
 */
int list_size(List *l);


/** Apply the same operator on each element of the list gieven a user define environment.
 @param l The list to process.
 @param f The operator (function) to apply to each element
 @see ReduceFunctor
 @return The eventually modified list
 @note If the elements are modified by the operator f, this function acts by side effect on the parameter l. The returned value is the same as the parameter l that is modified bye the function.
 This function sequentially apply the operator f on each element of the list with the user supplied environment defined by the abstract pointer userData. The operator is applied starting from the beginning of the list until the end. The value reurned by the operator when called on an element will replace the element.

Sort the list according to the provided ordering functor.
 @param l The list to sort.
 @param f The order to use
 @return The sorted list.
 @note This function acts by side effect on the parameter l. The returned value is the same as the parameter l that is modified by the function.
 */
//List *list_sort(List *l, OrderFunctor f);
/** @} */


List *list_reduce(List *l, ReduceFunctor f,void * env);
/** @} */

/**
 * @brief Sort a list in descending order.
 *
 * @param l The list to be sorted.
 * @return 1 or -1 depending on whether the list is sorted or not.
 */
int triee_liste_decroissant(List* l);



/* iterator*/

/// Iterator from the begining to the end
#define FORWARD_ITERATOR 1
/// Iterator from the end to the beginning
#define BACKWARD_ITERATOR 0


/**
 *	@brief Opaque definition of the ListIterator abstract data type.
 */
typedef struct s_ListIterator *ListIterator;

/**
 *	@brief Constructor of an iterator.
 * @param d the List to iterate
 * @param w the way the iterator will go (FORWARD_ITERATOR or BACKWARD_ITERATOR)
 * @return the correcly initialized iterator
 */
ListIterator list_iterator_create(List* d, unsigned char w);

/**
 *	@brief Destructor of an iterator.
 *  @param it the iterator to delete
 */
void list_iterator_delete(ListIterator it);

/**
 *	@brief Increment the iterator to the next position according to its direction.
 *  @param it the iterator to modify
 *	@return the modified iterator
 *	@note the parameter it is modified by side effect and is returned by the function
 */
Element list_iterator_next(ListIterator it);

/**
 *	@brief Acces to the value of the iterator.
 *  @param it the iterator to delete
 *  @return the value designed by the iterator
 */
Element list_iterator_value(ListIterator it);

int list_iterator_has_next(ListIterator it);


ListIterator list_iterator_begin(ListIterator it);

int list_iterator_delete_current(ListIterator it);

int list_iterator_end(ListIterator it);


/** @} */
#endif

