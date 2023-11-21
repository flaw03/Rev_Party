#ifndef UNINOMINALES_H
#define UNINOMINALES_H

typedef struct s_Resultat Resultat;



void unTour(char* fichier, FILE* logfile);
/**Fonction de mise en forme du vote uninominal à deux tours
@param fichier un fichier log permettant de stocker les calculs de l'algorithme
@param fichier fichier contenant les données
*/

void deuxTours(FILE* logfile, char* fichier);

#endif
