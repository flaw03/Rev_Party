#include <stdbool.h>

#define MAX_LIGNES 1024
#define MAX_COLONNES 1024
#define MAX_LINE_LENGTH 1024

#ifndef LECTURECSV_H
#define LECTURECSV_H

typedef struct s_CSVData *CSVData;

/**
*    Structure pour stocker les données CSV
*/

struct s_CSVData {
    char data[MAX_LIGNES][MAX_COLONNES][MAX_LINE_LENGTH];
    int ligne;
    int colonne;
};
CSVData createCSV();


void lireCSV(const char* filename, CSVData csvData);


void libererCSV(CSVData csvData);

#endif
