#ifndef JUGEMENT_H
#define JUGEMENT_H



/**
* @brief Fonction : trierVotes
* @brief Description : Trie tous les tableaux de votes d'une liste de candidats.
* @param lstCand : Liste de candidats.
*/
void trierVotes(ListCand* lstCand);

/**
* @brief Fonction : mediane
* @brief Description : Calcule la médiane d'un tableau d'entiers.
* @param tab : Tableau d'entiers.
* @return : La médiane des entiers.
*/
double mediane(Tableau tab);

/**
* @brief Fonction : afficherVote
* @brief Description : Affiche le tableau des votes dans un fichier log.
* @param tab : Tableau d'entiers représentant les votes.
* @param logfile : Pointeur vers le fichier journal où les logs sont affichés.
*/
void afficherVote(Tableau tab, FILE* logfile);

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
