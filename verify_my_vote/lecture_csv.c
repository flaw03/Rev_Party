#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture_csv.h"

/*
*    Equipe 17 : NDOYE Assane, SMETS Yoann, JOSEPH Wilkens Marc Johnley, MORELLATO Adrian
*/


/*
*   Fonction pour tester que le fichier en paramètre est bien un csv
*/

int isCSV(const char* filename) {
    const char* extension = strrchr(filename, '.');
    if (extension != NULL) {
        if (strcmp(extension, ".csv") == 0) {
            return 1; // Le fichier est .csv
        }
    }
    return 0; // Le fichier n'est pas .csv
}

/*
*    Fonction qui renvoie une ligne d'un hash doné
*/

int indice_sha(char* chaine,char* fichier){
    FILE* file = fopen(fichier,"r");
    if (file == NULL) {
        perror("Impossible d'ouvrir le fichier\n");
        exit(28);
    }
    char line[MAX_LINE_LENGTH];
    int colonne = 3;
	int indice =1;
    // Lire chaque ligne du fichier CSV
    while (fgets(line, MAX_LINE_LENGTH, file)) {

        char* token = strtok(line, ",");
        int colonneActuelle = 0;

        // Parcourir les tokens (colonnes)
        while (token != NULL) {
            // Si nous avons atteint la colonne souhaitée
            if (colonneActuelle == colonne) { //Colonne 3 = colonne des SHA
				if(strcmp(chaine,token) == 0){// HASH trouvé 
					fclose(file); 
					return indice;
				}
				indice++;   
            }
            // Obtenir le prochain token
            token = strtok(NULL, ",");
            colonneActuelle++;
        }
    }
    fclose(file);
	return -1; //Valeur non trouvée
}

/*
*    Fonction qui affiche le vote 
*/
void afficher_vote(const char *filename, int lineNumber) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
	printf("Vos vote : \n\n");

    char line[1024];
    int currentLine = 0;
    int fin = 0;

    while (!fin && fgets(line, sizeof(line), file)) { //concatène dans line les valeurs lues
        currentLine++;
        
        if (currentLine == lineNumber) {
            char *token = strtok(line, ",");
            int columnNumber = 1;
			int cpt = 1;
            while (token != NULL) {
                if (columnNumber >4) { // Les votes commencent à partir de la colonne 5
                    printf("Vote n°%d : %s\n", cpt, token);
					cpt++;
                }
                token = strtok(NULL, ",");
                columnNumber++;
            }
            fin = 1; // Sortir de la boucle après avoir trouvé la ligne souhaitée
        }
    }
    fclose(file);
}

