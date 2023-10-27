#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture_csv.h"

/*
*     Fonction création d'un CSV
*/

CSVData createCSV() {
    CSVData csvData = malloc(sizeof(struct s_CSVData));
    csvData->ligne = 0;
    csvData->colonne = 0;
    return csvData;
}

/*
*    Fonction pour lire le fichier CSV
*/

void lireCSV(const char* filename, CSVData csvData) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", filename);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];

    /*
    *     Lecture de chaque ligne du fichier csv
    */
    while (fgets(line, sizeof(line), file) && csvData->ligne < MAX_LIGNES) {
        char* token = strtok(line, ",");
        int colonne_actuelle = 0;
        while (token != NULL && colonne_actuelle < MAX_COLONNES) {
            /*
            *    On écrit chaque token au même emplacement dans csvData
            *    Puis on accède au prochain token
            *    Et ce sur toute les colonnes de la ligne
            */
            strcpy(csvData->data[csvData->ligne][colonne_actuelle], token);
            token = strtok(NULL, ",");
            colonne_actuelle++;
        }
        /*
        *    On met à jour les pointeurs
        */
        if (csvData->colonne < colonne_actuelle) {
            csvData->colonne = colonne_actuelle;
        }
        csvData->ligne++;
    }   

    fclose(file);
}

/*
*     Fonction pour libérer la mémoire allouée
*/ 
void libererCSV(CSVData csvData) {
    free(csvData);
}
