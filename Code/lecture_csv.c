#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIGNES 1024
#define MAX_COLONNES 1024
#define MAX_LINE_LENGTH 1024

/**
*    Structure pour stocker les données CSV
*/

typedef struct {
    char data[MAX_LIGNES][MAX_COLONNES][MAX_LINE_LENGTH];
    int ligne;
    int colonne;
}CSVData;

/*
*     Fonction création d'un CSV
*/
CSVData* createCSV() {
    CSVData* csvData = (CSVData*)malloc(sizeof(CSVData));
    csvData->ligne = 0;
    csvData->colonne = 0;
    return csvData;
}
/*
*    Fonction pour lire le fichier CSV
*/
CSVData* lireCSV(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", filename);
        return NULL;
    }


    CSVData* csvData = createCSV();

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
    return csvData;
}

/*
*     Fonction pour libérer la mémoire allouée
*/ 
void libererCSV(CSVData* csvData) {
    free(csvData);
}

/*
*    main pour tester
*/
//int main(int argc, char** argv) {
//    const char* filename = argv[1];
//    CSVData* data = lireCSV(filename);
//    printf("Lecture du fichier CSV : %s\n", argv[1]);
//    if (data) {
//        for (int i = 0; i < data->ligne; i++) {
//            for (int j = 0; j < data->colonne; j++) {
//                printf("%s\t", data->data[i][j]);
//            }
//            printf("\n");
//        }
//        libererCSV(data);
//    }
//    return 0;
//}