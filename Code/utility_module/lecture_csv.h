
#ifndef __LECTURE_CSV_H__
#define __LECTURE_CSV_H__

#include "utils_tab.h"
#include "utiles.h"
#include <stdbool.h>


/** \defgroup Constructors Contructors and destructors of the TAD.
 @{
 */
/** Enlève les sauts de ligne d'une chaine de caractère
    @param str la chaine à modifier
    @return la chaine modiée
*/
void removeNewline(char* str);


/**
 * @brief Obtient le nom du candidat à partir du fichier spécifié.
 *
 * @param filename Le nom du fichier à lire.
 * @param numColonne Le numéro de colonne à extraire.
 * @param isBallot Un booléen indiquant s'il s'agit une fichier csv de type balot ou dans cas contraire une matrice de duel
 * 
 * 
 * @return Un pointeur vers la chaîne de caractères représentant le nom du candidat.
 *         (N'oubliez pas de libérer la mémoire après utilisation.)
 */
char* obtenir_nom_Candidat(const char* filename, int numColonne, bool isBallot);

/**
 * @brief Affiche les votes correspondant à un hachage spécifié dans le fichier spécifié.
 *
 * @param filename Le nom du fichier à lire.
 * @param hash Le hachage à rechercher et afficher.
 */
void afficher_vote(const char* filename, char* hash);

/**
 * @brief Lit un fichier CSV contenant les votes sous la forme de bulletins et les transforme en matrice de duels.
 *
 * Cette fonction prend en entrée le nom d'un fichier CSV contenant les bulletins de vote, puis elle crée une matrice de duels
 * représentant les comparaisons deux à deux des candidats. La matrice résultante est stockée dans une structure Matrice.
 *
 * @param filename Le nom du fichier CSV contenant les bulletins de vote.
 * @param Matrice Un pointeur vers la structure Matrice pour stocker les données lues.
 * @return Le nombre d'électeurs dans le fichier.
 */
int lireBallot(char* filename, Matrice* Matrice);

/**
 * @brief Lit la matrice de duels à partir d'un fichier CSV et remplit la matrice de duels correspondante.
 *
 * Cette fonction prend en entrée le nom d'un fichier CSV contenant une matrice de duels, puis elle remplit la matrice
 * de duels représentant les comparaisons deux à deux des candidats. La matrice résultante est stockée dans une structure Matrice.
 *
 * @param filename Le nom du fichier CSV contenant la matrice de duels.
 * @param Matrice Un pointeur vers la structure Matrice pour stocker les données lues.
 * @return Le nombre d'électeurs dans le fichier.
 */
int lireMatriceDuel(char* filename, Matrice* Matrice);

/**
 * @brief Vérifie la validité des données présentes dans le fichier spécifié.
 *
 * @param filename Le nom du fichier à vérifier.
 * @return 1 si le fichier est valide, 0 sinon.
 */
int fichierValide(const char* filename);

/**
 * @brief Fonction permettant de factoriser la fonction fichierValide pour faciliter son appel.
 *
 * @param filename Le nom du fichier à vérifier.
 */
void verifFichier(const char* filename);


/**
 *  @brief Fonction créant une liste d'électeurs à partir d'un fichier et du candidat pour lequel il vote.
 * 
 *
 * @param lstElect Liste vide d'électeurs
 * @param lstCand Liste de candidats possibles
 * @param fichier Fichier contenant les données des électeurs et de leurs votes
 * @param tab Tableau qui va contenir les différents votes de l'électeur pour chaque candidat
 * 
 * 
 *  @return Une liste d'électeurs initialisée
*/
ListElect* getElecteur(ListElect* lstElect,ListCand* lstCand,char* fichier,Tableau tab);

/**
 * 
 *  @brief Fonction créant une liste de candidats à partir d'un fichier.csv
 *
 * 
 * @param lstCand Liste vide de candidats
 * @param fichier Le fichier contenant les données
 * 
 * 
 * @return Une liste de candidats initialisée
*/

ListCand* getCandidat(ListCand* lstCand, char* fichier);

/** 
 * @brief Fonction renvoyant l'indice colonne d'un fichier.csv de chaque candidat présent dans la liste
 * 
 * 
 * @param candidats Les candidats présent
 * @param fichier Le fichier.csv à analyser
 * @param tab le tableau vide qui contiendra les indices des candidats
 * 
 * 
 * @return le tableau contenant les indices des candidats
 * 
*/

int getIndice(Candidat* candidats, char* fichier);
/** 
 * @brief Fonction permettant de créer une liste d'electeurs ayant voté pour 2 candidats différents en choisissant celui qu'ils ont préféré.
 * 
 * 
 * @param lstElect liste vide
 * @param c1 Candidat 1
 * @param c2 Candidat 2
 * @param fichier le fichier contenant les votes et les informations des electeurs
 * 
 * @return Une liste d'électeurs
 * 
*/
ListElect* electeurs2ndTours2Candidats(ListElect* lstElect, Candidat* c1, Candidat* c2, char* fichier,FILE* logfile);

/**
 * @brief  Fonction permettant d'initialiser les votes d'une liste de candidat suivant les votes d'une liste d'électeurs
 * 
 * 
 * @param lstCand Liste de Candidat
 * @param lstElect Liste d'électeurs
 * @param fichier Fichier contenant les votes des électeurs
 * 
*/
void initJugement(ListCand* lstCand,ListElect* lstElect,char* fichier);

#endif
