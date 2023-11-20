#define MAX_LINE_LENGTH 1024

#define colonneID 0
#define colonneNom 3
#define colonneVote 4


#ifndef LECTURE_H
#define LECTURE_H

void removeNewline(char* str);

int getIndiceVote(int* votes, int taille);

Candidat* candidatAssocie(int nb, ListCand* lstCand);

ListElect* getElecteur(ListElect* lstElect, ListCand* lstCand, char* fichier, int* tab);

ListCand* getCandidat(ListCand* lstCand, char* fichier);

int* indice(ListCand* candidats, char* fichier, int* tab);

int getIndice(Candidat* candidats, char* fichier);

ListElect* electeurs2ndTours2Candidats(ListElect* lstElect, Candidat* c1, Candidat* c2, char* fichier);

ListElect* getElecteur2ndTour(ListElect* lstElect, ListCand* lstCand, char* fichier, int* tab);

#endif
