#define MAX_LINE_LENGTH 1024

#define colonneID 0
#define colonneNom 3
#define colonneVote 4


#ifndef LECTURE_H
#define LECTURE_H
/*-----------------------------------------------------------------*/

/** 
 *  @file lecture.h 
 *  @defgroup Constructors Contructors and destructors of the TAD.
 *  @{
 */





/** 
 * @brief Remove line breaks from a chain
 *
 * @par Profile
 * @parblock
 *	removeNewline : \f$\rightarrow \f$ void.
 * @endparblock
 * @param str the chain to modify
 * @return the modified chain
 * 
 */
void removeNewline(char* str);

/** 
 * @brief According to a vote array returns the vote index.
 * 
 * @par Profile
 * @parblock
 *	getIndiceVote : \f$\rightarrow \f$ int.
 * @endparblock
 * @param votes the voting array
 * @param taille the size of the array
 * @return the index
 * @pre
 *  0 \f$<\f$ taille
 *
 */
int getIndiceVote(int* votes, int taille);

/**
 * @brief Renvoie le candidat associé au nombre nb
 * 
 * @par Profile
 * @parblock
 *	candidatAssocie : \f$\rightarrow \f$ Candidat*.
 * @endparblock
 * @param nb a number
 * @param lstCand the list of candidates
 * @return the candidate associated with the number nb
 * @pre
 *  nb \f$<\f$ size_of_lstCand
 *
 */
Candidat* candidatAssocie(int nb, ListCand* lstCand);

/**
 * @brief Function creating a list of voters according to a .csv file
 * 
 * @par Profile
 * @parblock
 *	getElecteur : \f$\rightarrow \f$ ListElect*.
 * @endparblock
 * @param lstElect the empty voters list to fill
 * @param lstCand the list of Candidates to be associated with voters
 * @param fichier file containing data
 * @param tab The voters' vote array
 * @return a list of voters
 *
 */
ListElect* getElecteur(ListElect* lstElect, ListCand* lstCand, char* fichier, int* tab);

/**
 * @brief Function creating a list of candidates according to a .csv file
 *
 * @par Profile
 * @parblock
 *	getCandidat : \f$\rightarrow \f$ ListCand*.
 * @endparblock
 * @param lstCand the empty candidates list to fill
 * @param fichier file containing data
 * @return a list of candidates
 * 
 */
ListCand* getCandidat(ListCand* lstCand, char* fichier);

/** 
 * @brief Function returning the column index of a .csv file of each candidate present in the list
 * 
 * @par Profile
 * @parblock
 *	indice : \f$\rightarrow \f$ int*.
 * @endparblock
 * @param candidats The candidates present
 * @param fichier The .csv file to analyze
 * @param tab the empty array which will contain the indexes of the candidates
 * @return the array containing the candidates' indexes
 *
 */
int* indice(ListCand* candidats, char* fichier, int* tab);

/** 
 * @brief Function returning the column index of a candidate present in a .csv file and avoids calling a list
 * 
 * @par Profile
 * @parblock
 *	getIndice : \f$\rightarrow \f$ int.
 * @endparblock
 * @param candidat The candidate to look for
 * @param fichier The .csv file to analyze
 * @return the column index of the candidate in the .csv file
 *
 */
int getIndice(Candidat* candidats, char* fichier);

/** 
 * @brief Function allowing you to create a list of voters who voted for two different candidates by choosing the one they preferred.
 * 
 * @par Profile
 * @parblock
 *	electeurs2ndTours2Candidats : \f$\rightarrow \f$ ListElect*.
 * @endparblock
 * @param lstElect an empty list
 * @param c1 the Candidate 1
 * @param c2 the Candidate 2
 * @param fichier the file containing the votes and voter information
 * @return A list of voters
 *
 */

ListElect* electeurs2ndTours2Candidats(ListElect* lstElect, Candidat* c1, Candidat* c2, char* fichier,FILE* logfile);

/** 
 * @brief Function allowing you to create a list of voters who voted for a number of different candidates by choosing the one they preferred.
 * 
 * @par Profile
 * @parblock
 *	getElecteur2ndTour : \f$\rightarrow \f$ ListElect*.
 * @endparblock
 * @param lstElect an empty list
 * @param lstCand the list of candidates
 * @param fichier the file containing the votes and voter information
 * @param tab The array containing the votes of each voter
 * @return A list of voters
 *
 */
ListElect* getElecteur2ndTour(ListElect* lstElect, ListCand* lstCand, char* fichier, int* tab);

/** @} */



/** @} */

#endif
