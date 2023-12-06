#ifndef JUGEMENT_H
#define JUGEMENT_H

/**
* @brief Fonction : trier
* @brief Description : Sorts an array of integers in ascending order.
* @param tab : The table to be sorted.
* @param taille : Size of the table.
*/
void trier(int* tab, int taille);

/**
* @brief Fonction : trierVotes
* @brief Description : Sorts the votes for each candidate in the list in ascending order.
* @param lstCand : List of candidates.
* @param taille : Size of the list.
*/
void trierVotes(ListCand* lstCand, int taille);

/**
* @brief Fonction : mediane
* @brief Description : Calculates the median of an array of integers.
* @param tab : Table of integers.
* @param taille : Size of the table.
* @return : The median of the integers.
*/
double mediane(int* tab, int taille);

/**
* @brief Fonction : afficherVote
* @brief Description : Display table votes in a log file.
* @param tab : Array of integers representing votes.
* @param taille : Size of the array.
* @param logfile : Pointer to the log file where votes are displayed.
*/
void afficherVote(int* tab, int taille, FILE* logfile);

/**
* @brief Fonction : jugementMajoritaire
* @brief Description : Applies majority judgment to determine the winning candidate.
* @param lstCand : List of candidates.
* @param lstElect : List of elector.
* @param fichier : Name of the entry file.
* @param logfile : Pointer to the log file where votes are displayed.
* @return : The winning candidate.
*/
Candidat* jugementMajoritaire(ListCand* lstCand, ListElect* lstElect, char* fichier, FILE* logfile);

/** 
* @brief Fonction : voteJugementMajoritaireBallot
* @brief Description : Performs majority voting using an input file and generates a log file.
* @param fichier : Name of the entry file.
* @param logfile : Pointer to the log file where votes are displayed.
*/
void voteJugementMajoritaireBallot(char* fichier, FILE* logfile);

#endif
