#ifndef UNINOMINALES_H
#define UNINOMINALES_H

typedef struct s_Resultat Resultat;


/**@Fonction de test permettant de créer des electeurs votants pour des candidats connus de manière aléatoire.
@param lstElect Une liste d'électeurs vide
@param lstCand une liste de candidats
@param nbTest un nombre défini de test

@return une liste contenant nbTest electeurs
*/

ListElect* createTest(ListElect* lstElect, ListCand* lstCand, int nbTest);

/**Fonction de mise en forme du vote uninominal à un tour
@param fichier fichier contenant les données
@param fichier un fichier log permettant de stocker les calculs de l'algorithme




*/

void unTour(char* fichier, FILE* logfile);

/**Fonction de mise en forme du vote uninominal à deux tours
@param fichier un fichier log permettant de stocker les calculs de l'algorithme
@param fichier fichier contenant les données
*/

void deuxTours(FILE* logfile, char* fichier);

#endif
