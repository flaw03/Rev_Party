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
 Documentation of the implementation of the abstract data type List.
 @{
 */

/** \defgroup Type Type definition.
  @{
 */
/** Opaque definition of type List.
 */
typedef struct s_List List;
/** Définition of type ptrList : pointer to a List.
 */
typedef List * ptrList;



typedef struct s_element{
	int a ;
	int b;
	int p;
} * Element;

/** @} */

/*-----------------------------------------------------------------*/

/** \defgroup Functors Functions prototypes that could be used with some operators on List.
 @{
 */
/** Simple functor to be used with the list_map function.
 This functor receive as argument the value of a list element and must return the eventually modified value of the element.
 */
typedef int(*SimpleFunctor)(int,int,int);

/** Functor with user data to be used with the list_reduce operator.
  This functor receive as argument the value of a list element and an opaque pointer to user provided data and must return the eventually modified value of the element.
 */
typedef int (*ReduceFunctor)(Element,void *);

/** Functor to be used with the list_sort operator.
   This functor must implement a total ordering function (comp). When calling this functor with two list elements a and b, this functor must return true if (a comp b).
 */
typedef bool(*OrderFunctor)(int, int);
/** @} */

/*-----------------------------------------------------------------*/

/** \defgroup Constructors Contructors and destructors of the TAD.
 @{
 */
/** Implementation of the the constructor \c list from the specification.
 */
List *list_create(void);

/** Implementation of the the constructor \c push_back from the specification.
 @param l The list to modify
 @param p The weight of the candidate candidat1.
 @param candidat1 The value of the candidate a.
 @param candidat2 The value of the candidate b.
 @return The modified list
 Add the value v at the end of the list l.
 @note This function acts by side effect on the parameter l. The returned value is the same as the parameter l that is modified by the function.

 */
List *list_push_back(List *l, int p, int candidat1, int candidat2);

/** Destructor.
	Added by the implementation. Free ressources allocated by constructors.
 	@param l the adress of the list.
 	After calling this function, the list l becomes NULL.
 */
void list_delete(ptrList *l);
/** @} */

/*-----------------------------------------------------------------*/

/** \defgroup FrontBackOperators Insertion and removal of elements at front or back of the list.
 These operators have a time complexity in O(1).
 @{
 */
/** Add an element at the front of the list.
 	@param l The list to modify
 	@param p The weight of the candidate candidat1.
 	@param candidat1 The value of the candidate a.
 	@param candidat2 The value of the candidate b.
 	@return The modified list
 	@note This function acts by side effect on the parameter l. The returned value is the same as the parameter l that is modified by the function.
*/
List *list_push_front(List *l, int p, int candidat1, int candidat2);



/** Acces to the element at begining of the list.
 	@return the value of the front element of l.
	@pre !empty(l)
 */
int list_front(List *l);
/** Acces to the element at end of the list.
 	@return the value of the back element of l.
 	@pre !empty(l)
 */
int list_back(List *l);

/** Remove to the element at begining of the list.
 	@return The modified list
 	@note This function acts by side effect on the parameter l. The returned value is the same as the parameter l that is modified by the function.
  	@pre !empty(l)
 */
List *list_pop_front(List *l);

/** Remove to the element at end of the list.
 	@return The modified list
 	@note This function acts by side effect on the parameter l. The returned value is the same as the parameter l that is modified by the function.
 	@pre !empty(l)
 */
List *list_pop_back(List *l);
/** @} */

/*-----------------------------------------------------------------*/

/** \defgroup RandomAccessOperators Insertion and removal of elements at any position in the list.
 These operators have a worst case time complexity in O(n), with n the size of the list.
 @{
 */
/** Insert an element at a given position.
 	@param l The list to modify.
 	@param pos The position to insert.
 	@param p The weight of the candidate candidat1.
 	@param candidat1 The value of the candidate a.
 	@param candidat2 The value of the candidate b.
 	@return The modified list.
 	Insert an element in a list so that its position is given by p.
 	@pre 0 <= p <= list_size(l)
 	@note This function acts by side effect on the parameter l. The returned value is the same as the parameter l that is modified by the function.
 */
List *list_insert_at(List *l, int pos, int p, int candidat1,int candidat2);
/** Remove an element at a given position.
	 @param l The list to modify.
	 @param p The position of the element to be removed.
	 @return The modified list.
	 Remove the element located at position .
	 @pre 0 <= p < list_size(l)
	 @note This function acts by side effect on the parameter l. The returned value is the same as the parameter l that is modified by the function.
 */
List *list_remove_at(List *l, int p);
/** Acces to an element at a given position.
	 @param l The list to acces.
	 @param p The position to acces.
	 @return The value of the element at position p.
	 @pre 0 <= p < list_size(l)
 */
int list_at(List *l, int p);
/** @} */

/*-----------------------------------------------------------------*/

/** \defgroup UtilityOperators Operators allowing to access some properties or apply some processing on the whole list.
 @{
 */
/** Test if a list is empty.
 */
bool list_is_empty(List *l);
/** Give the number of elements of the list.
 */
int list_size(List *l);
/** Apply the same operator on each element of the list.
 	@param l The list to process.
 	@param f The operator (function) to apply to each element
 	@see SimpleFunctor
 	@return The eventually modified list
 	@note If the elements are modified by the operator f, this function acts by side effect on the parameter l. The returned value is the same as the parameter l that is modified bye the function.
 	This function sequentially apply the operator f on each element of the list, starting from the beginning of the list until the end. The value reurned by the operator when called on an element will replace the element.
*/
//List * list_map(List *l, SimpleFunctor f);


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

List * matriceCombatToGraphe(Matrice matrice);

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



int list_iterator_delete_current(ListIterator it);


int list_iterator_end(ListIterator it);





/** @} */

#endif

