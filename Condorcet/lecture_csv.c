#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lecture_csv.h"
#include "utils_tab.h"

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
*    Fonction qui renvoie le nom d'un candidat
*/


void obtenir_nom_Candidat(const char *filename,int numCandidat,char * nom_Candidat){
    FILE *file = fopen(filename, "r");
     if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(28);
    }
    char line[MAX_LINE_LENGTH];

    // lit la premier ligne 
    fgets(line, MAX_LINE_LENGTH, file);
    char* token = strtok(line, ",");
    int nb_colonne = 0;
    while (token != NULL && nb_colonne != numCandidat + COLONNE_SHA ){
        token = strtok(NULL, ",");
        nb_colonne ++;
    }
    if (token != NULL){
    char *positionTiret = strstr(token, "-");
    positionTiret = strstr(token, "- ");
        if (positionTiret != NULL ) {
            // Déplacer le pointeur au caractère après le tiret
            positionTiret++; 
            }

        char *sautDeLigne = strchr(positionTiret, '\n');
        while (sautDeLigne != NULL) {
            *sautDeLigne = '\0'; // Remplacer le saut de ligne par un caractère nul
            sautDeLigne = strchr(sautDeLigne + 1, '\n'); // Trouver le prochain saut de ligne
        }
        strcpy(nom_Candidat, positionTiret);
    }
    else{
        strcpy(nom_Candidat, "Candidat Introuvable ");
    }
}


/*
*    Fonction qui renvoie une ligne d'un hash doné
*/
void AffiherVote(const char* filename,char* hash){
    FILE* file = fopen(filename,"r"); 
    if (file == NULL) {
        perror("Impossible d'ouvrir le fichier\n");
        exit(28);
    }
    char line[MAX_LINE_LENGTH];
    // Lire chaque ligne du fichier CSV
    while (fgets(line, MAX_LINE_LENGTH, file)) {

        char *saveptr; 
        char* token ;
        token = strtok_r(line, ",",&saveptr);
        int colonne = 0;
        // Parcourir les tokens (colonnes)
        while (token != NULL && colonne <= COLONNE_SHA) {
            // Si nous avons atteint la colonne souhaitée
            if (colonne == COLONNE_SHA) { //Colonne 3 = colonne des SHA
				if(strcmp(token,hash) == 0){// HASH trouvé 
                    char nomCandidat[BUFFER_SIZE];
                    int cpt = 1;
                    token = strtok_r(NULL, ",", &saveptr);                    while (token != NULL){
                        obtenir_nom_Candidat(filename,atoi(token),nomCandidat);
                        printf("Vote n°%-2d : %s\n", cpt,nomCandidat);
					    cpt++;
                        token = strtok_r(NULL, ",", &saveptr);
                    }
					return;
				}

            }
            // Obtenir le prochain token
             token = strtok_r(NULL, ",", &saveptr);
            colonne++;
        }
    }
    printf("Électeur non trouvé dans la liste.\n");
    fclose(file);

}





Matrice lireCSVCondorcet(char* filename){
    FILE *file = fopen(filename, "r");
     if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(28);
    }
    char line[MAX_LINE_LENGTH];

    // lit la premier ligne 
    fgets(line, MAX_LINE_LENGTH, file);
    char* token = strtok(line, ",");
    int nb_colonne = 0;
    while (token != NULL){
        token = strtok(NULL, ",");
        nb_colonne ++;
    }
    nb_colonne -= MARGE;
    Matrice matrice = create_Matrice(nb_colonne,nb_colonne);
    init_Matrice(matrice,0);
    afficher_Matrice(matrice);
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char* token = strtok(line, ",");
        int colonne = 0;
        int vote;
        while (token != NULL) {
            if (colonne > MARGE - 1 ) { //Colonne 3 = colonne des SHA
                vote = atoi(token);
                if (vote > 0){
                    matrice->tableau[vote - 1][colonne - MARGE] += 1;
                }
            }
            token = strtok(NULL, ",");
            colonne++;
        }
    }
    fclose(file);
    return matrice;
}
