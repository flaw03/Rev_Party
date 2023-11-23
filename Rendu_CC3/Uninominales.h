#ifndef UNINOMINALES_H
#define UNINOMINALES_H

/**
 * @file Uninominales.h
 *	@defgroup defgroup Constructors Contructors and destructors of the TAD.
 * @{
 */




/**
 * @brief Opaque definition of the Resultat abstract data type.
 */
typedef struct s_Resultat Resultat;

/**
 * Fonction initialisant une structure Resultat
 * @param candidat Le candidat gagnant
 * @param nb le nombre de votes
 *
 * @return une structure Resultat
 */
Resultat affecter_resultat(Candidat* candidat, double nb);

/**
 * Fonction initialisant les votes des candidats suivant une liste d'électeurs
 * @param lstElect une liste d'électeurs
 * @param lstCand une liste de Candidats
 * @param fichier un fichier log permettant de stocker les calculs de l'algorithme
 *
 * @return Une liste de candidats avec leurs votes incrémentés
 */
ListCand* initVote(ListElect* lstElect, ListCand* lstCand, FILE* fichier);

/**
 * Fonction de vote uninominal à un tour
 * @param lstElect une liste d'électeurs
 * @param lstCand une liste de candidats
 * @param fichier un fichier log permettant de stocker les calculs de l'algorithme
 *
 * @return une structure Resultat contenant le candidat gagnant et son nombre de votes
 */
Resultat uninominal_un_tour(ListElect* lstElect, ListCand* lstCand, FILE* fichier);

/**
 * Fonction permettant d'initialiser un tableau de Candidats pour respecter le type d'une fonction lorsque on a un gagnant majoritaire
 * @param tab un tableau de candidat vide
 * @param candidat Le candidat ayant gagné majoritairement
 *
 * @return un tableau contenant un candidat ayant gagné majoritairement le vote uninominal à deux tours
 */
Candidat** createRetour(Candidat** tab, Candidat* candidat);

/**
 * Fonction permettant de récupérer dans un tableau les 2 candidats ayant eu le plus de vote
 * @param lstElect une liste d'électeurs
 * @param lstCand une liste de candidats
 * @param fichier un fichier log permettant de stocker les calculs de l'algorithme
 *
 * @return un tableau contenant les 2 candidats ayant le plus de votes OU un tableau contenant le candidat ayant eu la majorité absolue des voix
 */
Candidat** finalistes_uninominal_deux_tours(ListElect* lstElect, ListCand* lstCand, FILE* fichier);

/**
 * Fonction permettant de récupérer le candidat ayant le plus de voix entre les 2 candidats finalistes
 * @param lstElecteurs une liste d'électeurs
 * @param finalistes un tableau de finalistes
 * @param fichier un fichier log permettant de stocker les calculs de l'algorithme
 *
 * @return Un Resultat contenant le candidat gagnant et ses votes
 */
Resultat uninominal_2nd_Tours(ListElect* lstElecteurs, Candidat** finalistes, FILE* logfile);

/**
 * @Fonction de test permettant de créer des electeurs votants pour des candidats connus de manière aléatoire.
 * @param lstElect Une liste d'électeurs vide
 * @param lstCand une liste de candidats
 * @param nbTest un nombre défini de test
 *
 * @return une liste contenant nbTest electeurs
 */
ListElect* createTest(ListElect* lstElect, ListCand* lstCand, int nbTest);

/**
 * Fonction de mise en forme du vote uninominal à un tour
 * @param fichier fichier contenant les données
 * @param fichier un fichier log permettant de stocker les calculs de l'algorithme
 */
void unTour(char* fichier, FILE* logfile);

/**
 * Fonction de mise en forme du vote uninominal à deux tours
 * @param fichier un fichier log permettant de stocker les calculs de l'algorithme
 * @param fichier fichier contenant les données
 */
void deuxTours(FILE* logfile, char* fichier);

/** @} */



/** @} */

#endif
