#ifndef RENDU_H
#define RENDU_H

typedef struct s_Resultat Resultat;


Resultat affecter_resultat(Candidat* candidat, double nb);

ListCand* initVote(ListElect* lstElect, ListCand* lstCand, FILE* fichier);

Resultat uninominal_un_tour(ListElect* lstElect, ListCand* lstCand, FILE* fichier);

Candidat** createRetour(Candidat** tab, Candidat* candidat);

Candidat** finalistes_uninominal_deux_tours(ListElect* lstElect, ListCand* lstCand, FILE* fichier);

Resultat uninominal_2nd_Tours(ListElect* lstElecteurs, Candidat** finalistes, FILE* logfile);

ListElect* createTest(ListElect* lstElect, ListCand* lstCand, int nbTest);

void unTour(char* fichier, FILE* logfile);

void deuxTours(FILE* logfile, char* fichier);

#endif
