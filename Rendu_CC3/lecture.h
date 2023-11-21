#define MAX_LINE_LENGTH 1024

#define colonneID 0
#define colonneNom 3
#define colonneVote 4


#ifndef LECTURE_H
#define LECTURE_H
/*-----------------------------------------------------------------*/

/** \defgroup Constructors Contructors and destructors of the TAD.
 @{
 */

/**Fonction créant une liste d'électeurs selon un fichier.csv
@param lstElect la liste d'électeurs à remplir (vide)
@param lstCand la liste de Candidats à associer aux electeurs
@param fichier l'accès aux données
@param tab Le tableau de votes des electeurs
@return une liste d'electeurs

*/
ListElect* getElecteur(ListElect* lstElect, ListCand* lstCand, char* fichier, int* tab);

/**Fonction créant une liste de candidats à partir d'un fichier.csv

@param lstCand Liste vide de candidats
@param fichier Le fichier contenant les données
*/

ListCand* getCandidat(ListCand* lstCand, char* fichier);



int getIndice(Candidat* candidats, char* fichier);
/** Fonction permettant de créer une liste d'electurs ayant voté pour 2 candidats différents en choisissant celui qu'ils ont préféré.
@param lstElect liste vide
@param c1 Candidat 1
@param c2 Candidat 2
@param fichier le fichier contenant les votes et les informations des electeurs

@return Une liste d'électeurs

*/

ListElect* electeurs2ndTours2Candidats(ListElect* lstElect, Candidat* c1, Candidat* c2, char* fichier);

/** Fonction permettant de créer une liste d'electurs ayant voté pour un nombre de candidats différents en choisissant celui qu'ils ont préféré.
@param lstElect liste vide
@param lstCand la liste des candidats
@param fichier le fichier contenant les votes et les informations des electeurs
@param tab Le tableau contenant les votes de chaque electeur
@return Une liste d'électeurs


*/
ListElect* getElecteur2ndTour(ListElect* lstElect, ListCand* lstCand, char* fichier, int* tab);

#endif
