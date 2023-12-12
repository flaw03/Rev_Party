#ifndef JUGEMENT_H
#define JUGEMENT_H

/**
* @brief Fonction : trier
* @brief Description : Trie un tableau par ordre décroissant.
* @param tab : Le tableau à trier.
* @param taille : taille du tablau.
*/
void trier(int* tab, int taille);

//**
* @brief Fonction : trierVotes
* @brief Description : Trie tous les tableaux de votes d'une liste de candidats.
* @param lstCand : Liste de candidats.
* @param taille : Taille du tableau.
*/
void trierVotes(ListCand* lstCand, int taille);

/**
* @brief Fonction : mediane
* @brief Description : Calcule la médiane d'un tableau d'entiers.
* @param tab : Tableau d'entiers.
* @param taille : Taille du tableau.
* @return : La médiane des entiers.
*/
double mediane(int* tab, int taille);

/**
* @brief Fonction : afficherVote
* @brief Description : Affiche le tableau des votes dans un fichier log.
* @param tab : Tableau d'entiers représentant les votes.
* @param taille : Taille du tableau.
* @param logfile : Pointeur vers le fichier journal où les logs sont affichés.
*/
void afficherVote(int* tab, int taille, FILE* logfile);

/**
* @brief Fonction : jugementMajoritaire
* @brief Description : Applique le jugement majoritaire pour déterminer le candidat gagnant.
* @param lstCand : Liste de candidats.
* @param lstElect : Liste d'électeurs.
* @param fichier : Nom du fichier d'entrée.
* @param logfile : Pointeur vers le fichier journal où les logs sont affichés.
* @return : Le candidat gagnant.
*/
Candidat* jugementMajoritaire(ListCand* lstCand, ListElect* lstElect, char* fichier, FILE* logfile);

/** 
* @brief Fonction : voteJugementMajoritaireBallot
* @brief Description : Effectue un vote majoritaire avec tous les paramètres nécessaires pour simplifier un appel à la fonction
* @param fichier : Nom du fichier d'entrée contenant les informations.
* @param logfile : Pointeur vers le fichier journal où les logs sont affichés.
*/
void voteJugementMajoritaireBallot(char* fichier, FILE* logfile);


#endif
