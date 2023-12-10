
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
 * Obtient le nom du candidat à partir du fichier spécifié.
 *
 * @param filename Le nom du fichier à lire.
 * @param numColonne Le numéro de colonne à extraire.
 * @param isBallot Un booléen indiquant s'il s'agit d'une opération sur un bulletin de vote.
 * @return Un pointeur vers la chaîne de caractères représentant le nom du candidat.
 *         (N'oubliez pas de libérer la mémoire après utilisation.)
 */
char* obtenir_nom_Candidat(const char* filename, int numColonne, bool isBallot);

/**
 * Affiche les votes correspondant à un hachage spécifié dans le fichier spécifié.
 *
 * @param filename Le nom du fichier à lire.
 * @param hash Le hachage à rechercher et afficher.
 */
void afficher_vote(const char* filename, char* hash);

/**
 * Lit les bulletins de vote à partir du fichier spécifié et les stocke dans la structure Matrice.
 *
 * @param filename Le nom du fichier à lire.
 * @param Matrice Un pointeur vers la structure Matrice pour stocker les données lues.
 * @return Le nombre de bulletins de vote lus avec succès.
 */
int lireBallot(char* filename, Matrice* Matrice);

/**
 * Lit la matrice de duel à partir du fichier spécifié et la stocke dans la structure Matrice.
 *
 * @param filename Le nom du fichier à lire.
 * @param Matrice Un pointeur vers la structure Matrice pour stocker les données lues.
 * @return Le nombre de lignes (ou colonnes) de la matrice lue avec succès.
 */
int lireMatriceDuel(char* filename, Matrice* Matrice);

/**
 * Vérifie la validité des données présentes dans le fichier spécifié.
 *
 * @param filename Le nom du fichier à vérifier.
 * @return 1 si le fichier est valide, 0 sinon.
 */
int fichierValide(const char* filename);

/**
 * Fonction permettant de factoriser la fonction fichierValide pour faciliter son appel.
 *
 * @param filename Le nom du fichier à vérifier.
 */
void verifFichier(const char* filename);


ListElect* getElecteur(ListElect* lstElect, ListCand* lstCand, char* fichier, int* tab);

/**Fonction créant une liste de candidats à partir d'un fichier.csv

@param lstCand Liste vide de candidats
@param fichier Le fichier contenant les données
*/

ListCand* getCandidat(ListCand* lstCand, char* fichier);

/** Fonction renvoyant l'indice colonne d'un fichier.csv de chaque candidat présent dans la liste
@param candidats Les candidats présent
@param fichier Le fichier.csv à analyser
@param tab le tableau vide qui contiendra les indices des candidats

@return le tableau contenant les indices des candidats


*/

int getIndice(Candidat* candidats, char* fichier);
/** Fonction permettant de créer une liste d'electurs ayant voté pour 2 candidats différents en choisissant celui qu'ils ont préféré.
@param lstElect liste vide
@param c1 Candidat 1
@param c2 Candidat 2
@param fichier le fichier contenant les votes et les informations des electeurs

@return Une liste d'électeurs

*/

ListElect* electeurs2ndTours2Candidats(ListElect* lstElect, Candidat* c1, Candidat* c2, char* fichier,FILE* logfile);

/**Fonction permettant d'initialiser les votes d'une liste de candidat suivant les votes d'une liste d'électeurs
@param lstCand Liste de Candidat
@param lstElect Liste d'électeurs
@param fichier Fichier contenant les votes des électeurs
*/
void initJugement(ListCand* lstCand,ListElect* lstElect,char* fichier);

#endif
