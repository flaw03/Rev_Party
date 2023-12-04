#define MAX_LINE_LENGTH 1024

#define colonneID 0
#define colonneNom 3
#define colonneVote 4


#ifndef LECTURE_H
#define LECTURE_H
/*-----------------------------------------------------------------*/

/** \defgroup Constructors Contructors and destructors of the TAD.
 @{
 */
/** 
 * @brief Removes line breaks from a character string.
 * @param str The string to modify.
*/
void removeNewline(char* str);


ListElect* getElecteur(ListElect* lstElect, ListCand* lstCand, char* fichier, int* tab);

/**
 * @brief Create a list of candidates from a csv file
 * @param lstCand An empty list of candidates.
 * @param fichier The data file.
*/
ListCand* getCandidat(ListCand* lstCand, char* fichier);

/** 
 * @brief Returning the column index of a .csv file for each candidate in the list
 * @param candidats Les candidats présent
 * @param fichier zthe csv file
 * @param tab the initial empty table containing the candidate indices.
 * @return the table containing the candidate indexes.
*/
int getIndice(Candidat* candidats, char* fichier);

/** 
 * @brief create a list of electors who voted for 2 different candidates, choosing the one they preferred.
 * @param lstElect liste vide
 * @param c1 Candidate 1.
 * @param c2 Candidate 2.
 * @param The file containing votes and voter information.
 * @return Une liste d'électeurs
*/
ListElect* electeurs2ndTours2Candidats(ListElect* lstElect, Candidat* c1, Candidat* c2, char* fichier,FILE* logfile);

/**
 * @brief Initialize the votes of a candidate list according to the votes of a voter list.
 * @param lstCand Liste de Candidat
 * @param lstElect Liste d'électeurs
 * @param fichier Fichier contenant les votes des électeurs
*/
void initJugement(ListCand* lstCand,ListElect* lstElect,char* fichier);

#endif
