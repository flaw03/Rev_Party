
#ifndef __LECTURE_CSV_H__
#define __LECTURE_CSV_H__

#include "utils_tab.h"
#include "utiles.h"
#include <stdbool.h>





char * obtenir_nom_Candidat(const char *filename,int numColonne,bool isBallot);

void afficher_vote(const char* filename,char* hash);

int lireBallot(char* filename,Matrice *Matrice);

int lireMatriceDuel(char* filename,Matrice *Matrice);

int fichierValide(const char *filename);


void verifFichier(const char* filename);



/** \defgroup Constructors Contructors and destructors of the TAD.
 @{
 */
/** Enlève les sauts de ligne d'une chaine de caractère
    @param str la chaine à modifier
    @return la chaine modiée
*/
void removeNewline(char* str);


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
