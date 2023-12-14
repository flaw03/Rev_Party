#ifndef LISTESUTILES_H
#define LISTESUTILES_H
#include "utils_tab.h"
/** 
 * @defgroup Utils Utilitaires 
 * @brief Documentation des fonctions utilitaires pour le projet.
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
 * @brief Définition opaque du type abstrait de données Candidat.
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

/** \defgroup Constructors Constructeurs et destructeurs du TAD.
 @{
 */

/** Crée un nouvel électeur avec les informations spécifiées.
    @param nom Nom de famille de l'électeur.
    @param prenom Prénom de l'électeur.
    @param candidat Pointeur vers le candidat choisi par l'électeur.
    @return Un pointeur vers le nouvel électeur créé.
*/
Electeur* create_electeur(const char* nom, const char* prenom, Candidat* candidat);
/** Crée et initialise une liste vide d'électeurs.
    @return Un pointeur vers la nouvelle liste d'électeurs créée.
*/
ListElect* listElect_create(void);

/** Ajoute un électeur à la liste d'électeurs.
    @param l La liste d'électeurs à modifier.
    @param electeur Pointeur vers l'électeur à ajouter.
    @return La liste d'électeurs modifiée.
*/
ListElect* list_add_Electeur(ListElect* l, Electeur* electeur);


/** Supprime l'ensemble de la liste d'électeurs et libère la mémoire allouée.
    @param l La liste d'électeurs à supprimer.
*/
void listElect_delete(ListElect* l);

/** Crée un nouveau candidat avec les informations spécifiées.
    @param nom Nom de famille du candidat.
    @param prenom Prénom du candidat.
    @param age Âge du candidat.
    @return Un pointeur vers le nouveau candidat créé.
*/
Candidat* create_candidat(const char* nom, const char* prenom, int age);

/** Crée et initialise une liste vide de candidats.
    @return Un pointeur vers la nouvelle liste de candidats créée.
*/
ListCand* listCand_create(void);

/** Ajoute un candidat à la liste de candidats.
    @param l La liste de candidats à modifier.
    @param candidat Pointeur vers le candidat à ajouter.
    @return La liste de candidats modifiée.
*/
ListCand* listCand_add(ListCand* l, Candidat* candidat);

/** Supprime l'ensemble de la liste de candidats et libère la mémoire allouée.
    @param l La liste de candidats à supprimer.
*/
void listCand_delete(ListCand* l);

/** Libère la mémoire de chaque tableau présent dans chaque candidat.
   @param l La liste de candidats à parcourir.
*/
void tableauDelete(ListCand* l);

/** Affiche toutes les informations de chaque candidat dans la liste.
    @param l La liste de candidats à afficher.
*/
void printList(ListCand* l);

/** Obtient l'indice de la valeur minimale dans le tableau.
  @param tab Le tableau de votes.
  @return L'indice de la valeur minimale.
*/
int getIndiceVote(Tableau tab);

/** Retourne le candidat de l'indice donné.
  @param nb L'indice.
  @param lstCand La liste de candidats.
  @return Le candidat associé à l'indice donné.
*/
Candidat* candidatAssocie(int nb, ListCand* lstCand);

/** Crée et alloue la mémoire de chaque tableau présent dans chaque candidat.
 @param taille La taille du tableau à allouer.
 @param lstCand La liste de candidats.
*/
void createTableau(int taille, ListCand* lstCand);

/** Parcourt la chaîne de caractères et vérifie si elle contient un entier.
 * @param *str La chaîne de caractères.
 * @return 1 s'il contient un entier, 0 sinon.
*/
int isInteger(const char* str);

/** @} */

/** @} */

#endif
