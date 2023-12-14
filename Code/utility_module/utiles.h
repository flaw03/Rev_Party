#ifndef LISTESUTILES_H
#define LISTESUTILES_H
#include "utils_tab.h"
/** 
 * @defgroup Utils Utils 
 * @brief Documentation des fonctions "Utils" pour le projet.
 *@{
 */

/** 
 * @brief Définition opaque du type abstrait de données ListCand.
 */
typedef struct s_List_Cand ListCand;

/** 
 * @brief Définition opaque du type abstrait de données ListElect.
 */
typedef struct s_List_Electeur ListElect;

/** 
 * @brief Définition opaque du type abstrait de données Candidat .
 */
typedef struct s_Candidat Candidat;

/** 
 * @brief Définition opaque du type abstrait de données Electeur.
 */
typedef struct s_Electeur Electeur;


struct s_Candidat {
    char* nom;
    char* prenom;
    int age;
    int vote;
    Tableau jugement;
    struct s_Candidat* next;
};

struct s_Electeur {
    char* nom;
    char* prenom;
    struct s_Candidat* candidat;
    struct s_Electeur* next;
};

struct s_List_Electeur {
    struct s_Electeur* head;
    struct s_Electeur* tail;
    unsigned int size;
};

struct s_List_Cand {
    struct s_Candidat* head;
    struct s_Candidat* tail;
    unsigned int size;
};



/*-----------------------------------------------------------------*/

/** \defgroup Constructeurs et destructeurs du TAD.
 @{
 */

/** Crée un nouvel électeur avec les informations spécifiées.
    @param nom Nom de famille de l'électeur.
    @param prenom Prénom de l'électeur.
    @param candidat Pointeur sur le candidat choisi par l'électeur.
    @return Un pointeur sur le nouvel électeur correctement initialisé.
*/
Electeur* create_electeur(const char* nom, const char* prenom, Candidat* candidat);

/** Crée et initialise une liste vide d'électeur.
    @return Un pointeur sur la nouvelle liste correctement initialisé.
*/
ListElect* listElect_create(void);

/** Ajoute un électeur à la liste d'électeurs.
    @param l La liste d'électeurs à modifer.
    @param electeur Pointeur sur l'électeur à ajouter.
    @return La liste d'électeurs correctement modifiée.
*/
ListElect* list_add_Electeur(ListElect* l, Electeur* electeur);


/** Supprime entièrement la liste d'électeurs.
    @param l La liste d'électeurs à supprimer.
*/
void listElect_delete(ListElect* l);

/** Crée un nouveau candidat avec les informations spécifiées.
    @param nom Nom de famille du candidat.
    @param prenom Prénom du candidat.
    @param age Age du candidat.
    @return Un pointeur sur le nouveau candidat correctement initialisé.
*/
Candidat* create_candidat(const char* nom, const char* prenom, int age);

/** Crée et initialise une liste vide de candidat.
    @return Un pointeur sur la nouvelle liste correctement initialisé.
*/
ListCand* listCand_create(void);

/** Ajoute un candidat à la liste de candidats.
    @param l La liste de candidats à modifer.
    @param candidat Pointeur sur le candidat à ajouter.
    @return La liste de candidats correctement modifiée.
*/
ListCand* listCand_add(ListCand* l, Candidat* candidat);

/** Supprime entièrement la liste de candidats.
    @param l La liste de candidats à supprimer.
*/
void listCand_delete(ListCand* l);

/**Supprime le tableau de vote de chaque candidat.
   @param l La liste à supprimer.
*/
void tableauDelete(ListCand* l);

/** Affiche les informations de chaque candidat de la liste.
    @param l La liste de candidat à afficher.

*/
void printList(ListCand* l);

/** Obtenir l'indice de la valeur minimale du tableau. 
  @param tab Le tableau de vote.
  @return L'indice de la valeur minimale du tableau.
*/
int getIndiceVote(Tableau tab);

/** Renvoie le candidat à l'indice donné.
  @param nb L'indice du candidat.
  @param lstCand La liste de candidats.
  @return Le candidat à l'indice passé en paramètre.
*/
Candidat* candidatAssocie(int nb,ListCand* lstCand);

/** Crée et alloue de la mémoire pour chaque tableau de vote de chaque candidat.
 @param taille La taille du tableau.
 @param lstCand La liste de candidats: 
*/
void createTableau(int taille,ListCand* lstCand);


/** Vérifie si la chaine de caractère contient un entier.
 * @param *str La chaine de caractère.
 * @return 1 si elle contient un entier, 0 autrement.
*/
int isInteger(const char *str);



/** @} */

/** @} */

#endif
