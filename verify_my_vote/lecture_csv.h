#define MAX_LIGNES 1024
#define MAX_COLONNES 1024
#define MAX_LINE_LENGTH 1024

#ifndef LECTURECSV_H
#define LECTURECSV_H


int isCSV(const char* filename);

int indice_sha(char* chaine,char* fichier);

void afficher_vote(const char *filename, int lineNumber);

#endif
