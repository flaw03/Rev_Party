#ifndef LISTESUTILES_H
#define LISTESUTILES_H

typedef struct s_List_Cand ListCand;
typedef struct s_List_Electeur ListElect;
typedef struct s_Candidat Candidat;
typedef struct s_Electeur Electeur;


struct s_Candidat {
    char* nom;
    char* prenom;
    int age;
    int vote;
    int* jugement;
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

/**Free the array jugement of each candidate
   @param l The list of candidates to iterate on
*/
void tableauDelete(ListCand* l);
/**Displays all the informations of each candidate in the list.
    @param l The list of candidates to be displayed.

*/
void printList(ListCand* l);

/**Get the index of the minimal value in the array 
  @param votes The array of votes
  @param taille The size of the array

  @return The index of the minimal value
*/
int getIndiceVote(int* votes,int taille);

/**Return the candidat of the given index
  @param nb The index
  @param lstCand the list of candidates

  @return The Candidate associated to the given index
*/

Candidat* candidatAssocie(int nb,ListCand* lstCand);

/**Creates and allocate memory of each array present in each candidate
 @param taille The size of the array to allocate
 @param lstCand The list of candidates
 
*/

void createTableau(int taille,ListCand* lstCand);

#endif
