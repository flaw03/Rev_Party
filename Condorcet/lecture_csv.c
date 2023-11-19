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


char * obtenir_nom_Candidat(const char *filename,int numColonne){
    FILE *file = fopen(filename, "r");
     if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(28);
    }
    char line[MAX_LINE_LENGTH];


    // lit la premier ligne 
    fgets(line, MAX_LINE_LENGTH, file);
    fclose(file);
    char* token = strtok(line, ",");
    for (int  i = 0 ; i < MARGE + numColonne; i++){
        token = strtok(NULL, ",");
    }
    if (token != NULL) {
        // Allouer de la mémoire pour la chaîne et la copier
        size_t len = strcspn(token, "\n");
        if (len > 0 && token[len - 1] == '\r') {
            // Pour les fichiers texte Windows, enlever également le caractère de retour de chariot (\r)
            len--;
        }

        // Allouer de la mémoire pour la chaîne et la copier
        char *result = (char *)malloc(len + 1);
        if (result == NULL) {
            perror("Erreur lors de l'allocation de mémoire");
            exit(28);
        }

        strncpy(result, token, len);
        result[len] = '\0';  // Ajouter le caractère de fin de chaîne
        return result;
    } else {
        // Allouer de la mémoire pour la chaîne et la copier
        char *result = (char *)malloc(strlen("Candidat Introuvable") + 1);
        if (result == NULL) {
            perror("Erreur lors de l'allocation de mémoire");
            exit(28);
        }
        strcpy(result, "Candidat Introuvable");
        return result;
    }
}



/*
*    Fonction qui renvoie une ligne d'un hash doné
*/
void afficher_vote(const char* filename,char* hash){
    FILE* file = fopen(filename,"r"); 
    if (file == NULL) {
        perror("Impossible d'ouvrir le fichier\n");
        exit(28);
    }
    char line[MAX_LINE_LENGTH];
    // Lire chaque ligne du fichier CSV
    while (fgets(line, MAX_LINE_LENGTH, file)) {

        char* token ;
        token = strtok(line, ",");
        int colonne = 0;
        // Parcourir les tokens (colonnes)
        while (token != NULL && colonne <= COLONNE_SHA) {
            // Si nous avons atteint la colonne souhaitée
            if (colonne == COLONNE_SHA) { //Colonne 3 = colonne des SHA
				if(strcmp(token,hash) == 0){// HASH trouvé 
                    colonne ++;
                    token = strtok(NULL, ",");   
                    printf("Candidat |Vote\n");                 
                    while (token != NULL){
                        char * nomCandidat = obtenir_nom_Candidat(filename,colonne);
                        printf("%-30s|%s\n",nomCandidat,token);
                        token = strtok(NULL, ",");
					    colonne++;
                        free(nomCandidat);
                    }
					return;
				}

            }
            // Obtenir le prochain token
             token = strtok(NULL, ",");
            colonne++;
        }
    }
    printf("Électeur non trouvé dans la liste.\n");
    fclose(file);

}




int lireCSVCondorcet(char* filename,Matrice * matrice){
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
    int nombreVotant = 0;
    *matrice = create_Matrice(nb_colonne,nb_colonne);
    Matrice ligne = create_Matrice (1,nb_colonne);
    init_Matrice(*matrice,0);
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char* token = strtok(line, ",");
        int colonne = 0;
        nombreVotant++;
        while (token != NULL) {
            if (colonne > MARGE - 1 ) { //Colonne 3 = colonne des SHA 
                ligne->tableau[ligne->nb_ligne - 1][colonne - MARGE] = atoi(token);
            }
            token = strtok(NULL, ",");
            colonne++;
        }
        remplire_Matrice_Duel(*matrice,ligne);
    }
    delete_Matrice(ligne);
    fclose(file);
    return nombreVotant;
}
