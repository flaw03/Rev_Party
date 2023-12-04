#ifndef JUGEMENT_H
#define JUGEMENT_H

// Fonction : trier
// Description : Trie un tableau d'entiers en ordre croissant.
// @param tab : Tableau d'entiers à trier.
// @param taille : Taille du tableau.
void trier(int* tab, int taille);

// Fonction : trierVotes
// Description : Trie les votes de chaque candidat dans la liste en ordre croissant.
// @param lstCand : Liste des candidats.
// @param taille : Taille de la liste des candidats.
void trierVotes(ListCand* lstCand, int taille);


// Fonction : mediane
// Description : Calcule la médiane d'un tableau d'entiers.
// @param tab : Tableau d'entiers.
// @param taille : Taille du tableau.
// @return : La médiane des entiers dans le tableau.
double mediane(int* tab, int taille);

// Fonction : afficherVote
// Description : Affiche les votes d'un tableau dans un fichier de log.
// @param tab : Tableau d'entiers représentant les votes.
// @param taille : Taille du tableau de votes.
// @param logfile : Pointeur vers le fichier de log où afficher les votes.
void afficherVote(int* tab, int taille, FILE* logfile);

// Fonction : jugementMajoritaire
// Description : Applique le jugement majoritaire pour déterminer le candidat gagnant.
// @param lstCand : Liste des candidats.
// @param lstElect : Liste des électeurs.
// @param fichier : Nom du fichier d'entrée.
// @param logfile : Pointeur vers le fichier de log où afficher les résultats.
// @return : Le candidat gagnant selon le jugement majoritaire.
Candidat* jugementMajoritaire(ListCand* lstCand, ListElect* lstElect, char* fichier, FILE* logfile);

// Fonction : voteJugementMajoritaireBallot
// Description : Effectue un vote avec jugement majoritaire en utilisant un fichier d'entrée et génère un fichier de log.
// @param fichier : Nom du fichier d'entrée.
// @param logfile : Pointeur vers le fichier de log où afficher les résultats.
void voteJugementMajoritaireBallot(char* fichier, FILE* logfile);

#endif
