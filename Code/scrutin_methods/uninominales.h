#ifndef UNINOMINALES_H
#define UNINOMINALES_H

/**
 *  @file Uninominales.h
 *	@defgroup defgroup Constructeurs et destructeurs du TAD (Type Abstrait de Données).
 *  @{
 */

/**
 * @brief Définition opaque du type de données abstrait Resultat.
 */
typedef struct s_Resultat Resultat;

/**
 * @brief Fonction de vote uninominal à un tour.
 * 
 * @par Profil
 * @parblock
 *	uninominal_un_tour : \f$\rightarrow \f$ Resultat.
 * @endparblock
 * @param lstElect Une liste d'électeurs.
 * @param lstCand Une liste de candidats.
 * @param fichier Un fichier journal permettant de stocker les calculs de l'algorithme.
 * @return Une structure Resultat contenant le candidat gagnant et son nombre de votes.
 */
Resultat uninominal_un_tour(ListElect* lstElect, ListCand* lstCand, FILE* fichier);


/**
 * @brief Fonction permettant de récupérer à partir d'un tableau les deux candidats ayant le plus de votes.
 * 
 * @par Profil
 * @parblock
 *	finalistes_uninominal_deux_tours : \f$\rightarrow \f$ Candidat**.
 * @endparblock
 * @param lstElect Une liste d'électeurs.
 * @param lstCand Une liste de candidats.
 * @param fichier Un fichier journal permettant de stocker les calculs de l'algorithme.
 * @return Un tableau contenant les deux candidats avec le plus de votes OU un tableau contenant le candidat ayant eu la majorité absolue de votes.
 */
Candidat** finalistes_uninominal_deux_tours(ListElect* lstElect, ListCand* lstCand, FILE* fichier);

/**
 * @brief Fonction permettant de récupérer le candidat avec le plus de votes entre les deux candidats finalistes.
 * 
 * @par Profil
 * @parblock
 *	uninominal_2nd_Tours : \f$\rightarrow \f$ Resultat.
 * @endparblock
 * @param lstElecteurs Une liste d'électeurs.
 * @param finalistes Un tableau de finalistes.
 * @param fichier Un fichier journal permettant de stocker les calculs de l'algorithme.
 * @return Une structure Resultat contenant le candidat gagnant et ses votes.
 */
Resultat uninominal_2nd_Tours(ListElect* lstElecteurs, Candidat** finalistes, FILE* logfile);

/**
 * @brief Fonction de test pour créer des électeurs votants pour des candidats connus de manière aléatoire.
 * 
 * @par Profil
 * @parblock
 *	createTest : \f$\rightarrow \f$ ListElect*.
 * @endparblock
 * @param lstElect Une liste vide d'électeurs.
 * @param lstCand Une liste de candidats.
 * @param nbTest Un nombre défini de tests.
 * @return Une liste contenant nbTest électeurs.
 */
ListElect* createTest(ListElect* lstElect, ListCand* lstCand, int nbTest);

/**
 * @brief Fonction de mise en forme du vote uninominal à un tour.
 * 
 * @par Profil
 * @parblock
 *	unTour : \f$\rightarrow \f$ void.
 * @endparblock
 * @param fichier Fichier contenant les données.
 * @param fichier Un fichier journal permettant de stocker les calculs de l'algorithme.
 */
void unTour(char* fichier, FILE* logfile);

/**
 * @brief Fonction de mise en forme du vote uninominal à deux tours.
 * 
 * @par Profil
 * @parblock
 *	deuxTours : \f$\rightarrow \f$ void.
 * @endparblock
 * @param Un fichier journal permettant de stocker les calculs de l'algorithme.
 * @param fichier Fichier contenant les données.
 */
void deuxTours(FILE* logfile, char* fichier);

/** @} */

/** @} */

#endif
