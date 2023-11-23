#ifndef LISTESUTILES_H
#define LISTESUTILES_H


/**
 * @file Utiles.h
 *	@defgroup defgroup Constructors Contructors and destructors of the TAD.
 * @{
 */


/**
 * @brief Opaque definition of the ListCand abstract data type.
 */
typedef struct s_List_Cand ListCand;

/**
 * @brief Opaque definition of the ListElect abstract data type.
 */
typedef struct s_List_Electeur ListElect;

/**
 * @brief Opaque definition of the Candidat abstract data type.
 */
typedef struct s_Candidat Candidat;

/**
 * @brief Opaque definition of the Electeur abstract data type.
 */
typedef struct s_Electeur Electeur;

struct s_Candidat {
    char* nom;
    char* prenom;
    int age;
    int vote;
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


/** 
 * @brief Creates a new voter with the specified information.
 *
 * @par Profile
 * @parblock
 *  create_electeur : \f$\rightarrow\f$ Electeur*.
 * @endparblock
 * @param nom Last name of the voter.
 * @param prenom First name of the voter.
 * @param candidat Pointer to the candidate chosen by the voter.
 * @return A pointer to the newly created voter.
 */
Electeur* create_electeur(const char* nom, const char* prenom, Candidat* candidat);

/** @brief Creates and initializes an empty list of voters.
    @return A pointer to the newly created list of voters.
*/
ListElect* listElect_create(void);

/** @brief Adds an electeur to the list of electeurs.
    @param l The list of electeurs to modify.
    @param electehr Pointer to the electeur to be added.
    @return The modified list of electerrs.
*/
ListElect* list_add_Electeur(ListElect* l, Electeur* electeur);


/** @brief Deletes the entire list of electeurs and frees allocated memory.
    @param l The list of electeurs to be deleted.
*/
void listElect_delete(ListElect* l);

/** @brief Creates a new candidate with the specified information.
    @param nom Last name of the candidate.
    @param prenom First name of the candidate.
    @param age Age of the candidate.
    @return A pointer to the newly created candidate.
*/
Candidat* create_candidat(const char* nom, const char* prenom, int age);

/** @brief Creates and initializes an empty list of candidates.
    @return A pointer to the newly created list of candidates.
*/
ListCand* listCand_create(void);

/** @brief Adds a candidate to the list of candidates.
    @param l The list of candidates to modify.
    @param candidat Pointer to the candidate to be added.
    @return The modified list of candidates.
*/
ListCand* listCand_add(ListCand* l, Candidat* candidat);

/** @brief Deletes the entire list of candidates and frees allocated memory.
    @param l The list of candidates to be deleted.
*/
void listCand_delete(ListCand* l);

/** @brief Displays all the informations of each candidate in the list.
    @param l The list of candidates to be displayed.

*/
void printList(ListCand* l);
#endif
