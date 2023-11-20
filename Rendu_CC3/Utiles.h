#ifndef LISTESUTILES_H
#define LISTESUTILES_H

typedef struct s_List_Cand ListCand;
typedef struct s_List_Electeur ListElect;
typedef struct s_Candidat Candidat;
typedef struct s_Electeur Electeur;


/*-----------------------------------------------------------------*/

/** \defgroup Constructors Contructors and destructors of the TAD.
 @{
 */

/** Creates a new voter with the specified information.
    @param nom Last name of the voter.
    @param prenom First name of the voter.
    @param candidat Pointer to the candidate chosen by the voter.
    @return A pointer to the newly created voter.
*/
Electeur* create_electeur(const char* nom, const char* prenom, Candidat* candidat);
/** Creates and initializes an empty list of voters.
    @return A pointer to the newly created list of voters.
*/
ListElect* listElect_create(void);

/** Adds an electeur to the list of electeurs.
    @param l The list of electeurs to modify.
    @param electehr Pointer to the electeur to be added.
    @return The modified list of electerrs.
*/
ListElect* list_add_Electeur(ListElect* l, Electeur* electeur);


/** Deletes the entire list of electeurs and frees allocated memory.
    @param l The list of electeurs to be deleted.
*/
void listElect_delete(ListElect* l);

/** Creates a new candidate with the specified information.
    @param nom Last name of the candidate.
    @param prenom First name of the candidate.
    @param age Age of the candidate.
    @return A pointer to the newly created candidate.
*/
Candidat* create_candidat(const char* nom, const char* prenom, int age);

/** Creates and initializes an empty list of candidates.
    @return A pointer to the newly created list of candidates.
*/
ListCand* listCand_create(void);

/** Adds a candidate to the list of candidates.
    @param l The list of candidates to modify.
    @param candidat Pointer to the candidate to be added.
    @return The modified list of candidates.
*/
ListCand* listCand_add(ListCand* l, Candidat* candidat);

/** Deletes the entire list of candidates and frees allocated memory.
    @param l The list of candidates to be deleted.
*/
void listCand_delete(ListCand* l);

/**Displays all the informations of each candidate in the list.
    @param l The list of candidates to be displayed.

*/

void printList(ListCand* l);
#endif
