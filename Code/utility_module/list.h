/*-----------------------------------------------------------------*/
/*
 Interface pour l'implémentation du TAD List pour le projet.
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

/** \defgroup Type Définition du type.
  @{
 */
/** Définition opaque du type List.
 */
typedef struct s_List List;
/** Définition du type ptrList : pointeur vers une List.
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

/** \defgroup Constructors Constructeurs et destructeurs du TAD.
 @{
 */
/** Implémentation du constructeur \c list selon la spécification.
 */
List *list_create(void);

/** Implémentation du constructeur \c push_back selon la spécification.
 @param l La liste à modifier
 @param p Le poids du candidat candidat1.
 @param candidat1 La valeur du candidat a.
 @param candidat2 La valeur du candidat b.
 @return La liste modifiée
 Ajoute la valeur v à la fin de la liste l.
 @note Cette fonction agit par effet de côté sur le paramètre l. La valeur retournée est la même que le paramètre l qui est modifié par la fonction.

 */
List *list_push_back(List *l, int p, int candidat1, int candidat2);

/** Destructeur.
    Ajouté par l'implémentation. Libère les ressources allouées par les constructeurs.
    @param l l'adresse de la liste.
    Après l'appel de cette fonction, la liste l devient NULL.
 */
void list_delete(ptrList *l);
/** @} */

/*-----------------------------------------------------------------*/

/** \defgroup FrontBackOperators Insertion et suppression d'éléments en tête ou en fin de liste.
 Ces opérateurs ont une complexité temporelle en O(1).
 @{
 */
/** Ajoute un élément en tête de la liste.
    @param l La liste à modifier
    @param p Le poids du candidat candidat1.
    @param candidat1 La valeur du candidat a.
    @param candidat2 La valeur du candidat b.
    @return La liste modifiée
    @note Cette fonction agit par effet de côté sur le paramètre l. La valeur retournée est la même que le paramètre l qui est modifié par la fonction.
*/
List *list_push_front(List *l, int p, int candidat1, int candidat2);

/** Accède à l'élément en début de liste.
    @return la valeur de l'élément en tête de l.
    @pre !empty(l)
 */
int list_front(List *l);
/** Accède à l'élément en fin de liste.
    @return la valeur de l'élément en fin de l.
    @pre !empty(l)
 */
int list_back(List *l);

/** Supprime l'élément en début de liste.
    @return La liste modifiée
    @note Cette fonction agit par effet de côté sur le paramètre l. La valeur retournée est la même que le paramètre l qui est modifié par la fonction.
    @pre !empty(l)
 */
List *list_pop_front(List *l);

/** Supprime l'élément en fin de liste.
    @return La liste modifiée
    @note Cette fonction agit par effet de côté sur le paramètre l. La valeur retournée est la même que le paramètre l qui est modifié par la fonction.
    @pre !empty(l)
 */
List *list_pop_back(List *l);
/** @} */

/*-----------------------------------------------------------------*/

/** \defgroup RandomAccessOperators Insertion et suppression d'éléments à n'importe quelle position dans la liste.
 Ces opérateurs ont une complexité temporelle dans le pire des cas en O(n), avec n la taille de la liste.
 @{
 */
/** Insère un élément à une position donnée.
    @param l La liste à modifier.
    @param pos La position d'insertion.
    @param p Le poids du candidat candidat1.
    @param candidat1 La valeur du candidat a.
    @param candidat2 La valeur du candidat b.
    @return La liste modifiée.
    Insère un élément dans une liste de manière à ce que sa position soit donnée par p.
    @pre 0 <= p <= list_size(l)
    @note Cette fonction agit par effet de côté sur le paramètre l. La valeur retournée est la même que le paramètre l qui est modifié par la fonction.
 */
List *list_insert_at(List *l, int pos, int p, int candidat1,int candidat2);
/** Supprime un élément à une position donnée.
     @param l La liste à modifier.
     @param p La position de l'élément à supprimer.
     @return La liste modifiée.
     Supprime l'élément situé à la position p.
     @pre 0 <= p < list_size(l)
     @note Cette fonction agit par effet de côté sur le paramètre l. La valeur retournée est la même que le paramètre l qui est modifié par la fonction.
 */
List *list_remove_at(List *l, int p);
/** Accède à un élément à une position donnée.
     @param l La liste à accéder.
     @param p La position à accéder.
     @return La valeur de l'élément à la position p.
     @pre 0 <= p < list_size(l)
 */
int list_at(List *l, int p);
/** @} */

/*-----------------------------------------------------------------*/

/** \defgroup UtilityOperators Opérateurs permettant d'accéder à certaines propriétés ou d'appliquer certains traitements sur toute la liste.
 @{
 */
/** Teste si une liste est vide.
 */
bool list_is_empty(List *l);
/** Donne le nombre d'éléments de la liste.
 */
int list_size(List *l);
/** Applique le même opérateur sur chaque élément de la liste.
    @param l La liste à traiter.
    @param f L'opérateur (fonction) à appliquer à chaque élément
    @see SimpleFunctor
    @return La liste éventuellement modifiée
    @note Si les éléments sont modifiés par l'opérateur f, cette fonction agit par effet de côté sur le paramètre l. La valeur retournée est la même que le paramètre l qui est modifié par la fonction.
    Cette fonction applique séquentiellement l'opérateur f sur chaque élément de la liste, en commençant par le début de la liste jusqu'à la fin. La valeur renvoyée par l'opérateur lorsqu'il est appelé sur un élément remplacera l'élément.
*/
//List * list_map(List *l, SimpleFunctor f);


/** Applique le même opérateur sur chaque élément de la liste en utilisant un environnement défini par l'utilisateur.
 @param l La liste à traiter.
 @param f L'opérateur (fonction) à appliquer à chaque élément
 @see ReduceFunctor
 @return La liste éventuellement modifiée
 @note Si les éléments sont modifiés par l'opérateur f, cette fonction agit par effet de côté sur le paramètre l. La valeur retournée est la même que le paramètre l qui est modifié par la fonction.
 Cette fonction applique séquentiellement l'opérateur f sur chaque élément de la liste avec l'environnement fourni par le pointeur abstrait userData. L'opérateur est appliqué en commençant par le début de la liste jusqu'à la fin. La valeur renvoyée par l'opérateur lorsqu'il est appelé sur un élément remplacera l'élément.

Trie la liste selon l'opérateur d'ordonnancement fourni.
 @param l La liste à trier.
 @param f L'ordre à utiliser
 @return La liste triée.
 @note Cette fonction agit par effet de côté sur le paramètre l. La valeur retournée est la même que le paramètre l qui est modifié par la fonction.
 */
//List *list_sort(List *l, OrderFunctor f);
/** @} */


List *list_reduce(List *l, ReduceFunctor f,void * env);
/** @} */

/**
 * @brief Trie une liste par ordre décroissant.
 *
 * @param l La liste à trier.
 * @return 1 ou -1 en fonction de si la liste est triée ou non.
 */
int triee_liste_decroissant(List* l);

/* itérateur */

/// Itérateur du début à la fin
#define FORWARD_ITERATOR 1
/// Itérateur de la fin au début
#define BACKWARD_ITERATOR 0


/**
 *	@brief Définition opaque du type abstrait de données ListIterator.
 */
typedef struct s_ListIterator *ListIterator;

/**
 *	@brief Constructeur d'un itérateur.
 * @param d la List à itérer
 * @param w la direction que prendra l'itérateur (FORWARD_ITERATOR ou BACKWARD_ITERATOR)
 * @return l'itérateur correctement initialisé
 */
ListIterator list_iterator_create(List* d, unsigned char w);

/**
 *	@brief Destructeur d'un itérateur.
 *  @param it l'itérateur à supprimer
 */
void list_iterator_delete(ListIterator it);

/**
 *	@brief Incrémente l'itérateur à la position suivante selon sa direction.
 *  @param it l'itérateur à modifier
 *	@return l'itérateur modifié
 *	@note le paramètre it est modifié par effet de côté et est retourné par la fonction
 */
Element list_iterator_next(ListIterator it);

/**
 *	@brief Accède à la valeur de l'itérateur.
 *  @param it l'itérateur à supprimer
 *  @return la valeur désignée par l'itérateur
 */
Element list_iterator_value(ListIterator it);

/**Renvoie s'il y a encore des éléments à parcourir.
 */
int list_iterator_has_next(ListIterator it);

/**Renvoie l'élément sur lequel l'itérateur commence à itérer.
 */ 
ListIterator list_iterator_begin(ListIterator it);

/**Supprime l'élément courant de l'itérateur.
 */ 
int list_iterator_delete_current(ListIterator it);

/**Renvoie si l'itérateur a atteint la fin de la liste.
 */ 
int list_iterator_end(ListIterator it);

/** @} */
#endif
