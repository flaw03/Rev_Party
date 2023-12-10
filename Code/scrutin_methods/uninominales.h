#ifndef UNINOMINALES_H
#define UNINOMINALES_H

/**
 *  @file Uninominales.h
 *	@defgroup defgroup Constructors Contructors and destructors of the TAD.
 *  @{
 */




/**
 * @brief Opaque definition of the Resultat abstract data type.
 */
typedef struct s_Resultat Resultat;

/**
 * @brief Function initializing a structure Resultat
 * 
 * @par Profile
 * @parblock
 *	affecter_resultat : \f$\rightarrow \f$ Resultat.
 * @endparblock
 * @param candidat The winning candidate
 * @param nb the number of votes
 *
 * @return a structure Resultat
 * 
 */
Resultat affecter_resultat(Candidat* candidat, double nb);

/**
 * @brief Function initializing the votes of candidates following a list of voters
 * 
 * @par Profile
 * @parblock
 *	initVote : \f$\rightarrow \f$ ListCand*.
 * @endparblock
 * @param lstElect a list of voters
 * @param lstCand a list of candidates
 * @param fichier a log file allowing you to store the algorithm calculations
 *
 * @return A list of candidates with their incremented votes
 * 
 */
ListCand* initVote(ListElect* lstElect, ListCand* lstCand, FILE* fichier);

/**
 * @brief First-past-the-post voting function
 * 
 * @par Profile
 * @parblock
 *	uninominal_un_tour : \f$\rightarrow \f$ Resultat.
 * @endparblock
 * @param lstElect a list of voters
 * @param lstCand a list of candidates
 * @param fichier a log file allowing you to store the algorithm calculations
 * @return a Resultat structure containing the winning candidate and their number of votes
 *
 */
Resultat uninominal_un_tour(ListElect* lstElect, ListCand* lstCand, FILE* fichier);

/**
 * @brief Function allowing you to initialize an array of Candidates to respect the type of a function when you have a majority winner
 * 
 * @par Profile
 * @parblock
 *	createRetour : \f$\rightarrow \f$ Candidat**.
 * @endparblock
 * @param tab an empty candidate array
 * @param candidat The candidate who won by a majority
 * @return an array containing a candidate who won by a majority in the two-round single-member vote
 * 
 */
Candidat** createRetour(Candidat** tab, Candidat* candidat);

/**
 * @brief Function allowing you to retrieve from an array the two candidates with the most votes
 * 
 * @par Profile
 * @parblock
 *	finalistes_uninominal_deux_tours : \f$\rightarrow \f$ Candidat**.
 * @endparblock
 * @param lstElect a list of voters
 * @param lstCand a list of candidates
 * @param fichier a log file allowing you to store the algorithm calculations
 * @return an array containing the two candidates with the most votes OR an array containing the candidate having had the absolute majority of votes
 * 
 */
Candidat** finalistes_uninominal_deux_tours(ListElect* lstElect, ListCand* lstCand, FILE* fichier);

/**
 * @brief Function allowing you to retrieve the candidate with the most votes between the two finalist candidates
 * 
 * @par Profile
 * @parblock
 *	uninominal_2nd_Tours : \f$\rightarrow \f$ Resultat.
 * @endparblock
 * @param lstElecteurs a list of voters
 * @param finalistes an array of finalists
 * @param fichier a log file allowing you to store the algorithm calculations
 * @return A Resultat structure containing the winning candidate and their votes
 * 
 */
Resultat uninominal_2nd_Tours(ListElect* lstElecteurs, Candidat** finalistes, FILE* logfile);

/**
 * @brief Test function to create voting electors for known candidates randomly.
 * 
 * @par Profile
 * @parblock
 *	createTest : \f$\rightarrow \f$ ListElect*.
 * @endparblock
 * @param lstElect an empty list of voters
 * @param lstCand a list of candidates
 * @param nbTest a defined number of tests
 * @return a list containing nbTest voters
 * 
 */
ListElect* createTest(ListElect* lstElect, ListCand* lstCand, int nbTest);

/**
 * @brief First-past-the-post vote formatting function
 * 
 * @par Profile
 * @parblock
 *	unTour : \f$\rightarrow \f$ void.
 * @endparblock
 * @param fichier file containing data
 * @param fichier a log file allowing you to store the algorithm calculations
 * 
 */
void unTour(char* fichier, FILE* logfile);

/**
 * @brief Two-round first-past-the-post vote formatting function
 * 
 * @par Profile
 * @parblock
 *	deuxTours : \f$\rightarrow \f$ void.
 * @endparblock
 * @param a log file allowing you to store the algorithm calculations
 * @param fichier fichier file containing data
 * 
 */
void deuxTours(FILE* logfile, char* fichier);

/** @} */



/** @} */

#endif
