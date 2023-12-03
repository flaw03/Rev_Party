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
        if (strcmp(extension, ".csv") != 0) {
            return 1;
        }
    }
    return 0;
}

/*
*    Fonction qui renvoie le nom d'un candidat
*/


char * formatage_nomCandidat(char * nom){
        if (nom != NULL) {
        // Allouer de la mémoire pour la chaîne et la copier
        size_t len = strcspn(nom, "\n");
        if (len > 0 && nom[len - 1] == '\r') {
            // Pour les fichiers texte Windows, enlever également le caractère de retour de chariot (\r)
            len--;
        }

        // Allouer de la mémoire pour la chaîne et la copier
        char *result = (char *)malloc(len + 1);
        if (result == NULL) {
            perror("Erreur lors de l'allocation de mémoire");
            exit(28);
        }

        strncpy(result, nom, len);
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

char * obtenir_nom_Candidat_txt(const char *filename,int numColonne){
    FILE *file = fopen(filename, "r");
     if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(28);
    }
    char line[MAX_LINE_LENGTH];

    if (fgets(line, MAX_LINE_LENGTH, file) == NULL){
        perror("fegts");
        exit(1);
    };
    const char *delimiteur = "\t";
    char* token = strtok(line,delimiteur);
    int nb_candidat = 0;
    while (token != NULL && nb_candidat < numColonne){
        token = strtok(NULL,delimiteur);
        nb_candidat ++;
    }
    return formatage_nomCandidat(token);
}


char * obtenir_nom_Candidat_csv(const char *filename,int numColonne){
    FILE *file = fopen(filename, "r");
     if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(28);
    }
    char line[MAX_LINE_LENGTH];


    // lit la premier ligne 
    if (fgets(line, MAX_LINE_LENGTH, file) == NULL){
        perror("fegts");
        exit(1);
    };
    fclose(file);
    char* token = strtok(line, ",");
    for (int  i = 0 ; i < MARGE + numColonne; i++){
        token = strtok(NULL, ",");
    }
    return formatage_nomCandidat(token);
}

char * obtenir_nom_Candidat(const char *filename,int numColonne){
    if (isCSV(filename)){
        return obtenir_nom_Candidat_csv(filename,numColonne);
    }else{
        return obtenir_nom_Candidat_txt(filename,numColonne);
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
    isCSV(filename);
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



int lireCSVCondorcet(char* filename,Matrice *matrice){
    FILE *file = fopen(filename, "r");
     if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(28);
    }
    char line[MAX_LINE_LENGTH];

    // lit la premier ligne 
     if (fgets(line, MAX_LINE_LENGTH, file) == NULL){
        perror("fegts");
        exit(1);
    };
    char* token = strtok(line, ",");
    int nb_candidat = 0;
    while (token != NULL){
        token = strtok(NULL, ",");
        nb_candidat ++;
    }
    nb_candidat -= MARGE;
    int nombreVotant = 0;
    
    *matrice = create_Matrice(nb_candidat,nb_candidat);
    init_Matrice(*matrice,0);
    
    Tableau tableauVote = create_Tableau(nb_candidat);
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char* token = strtok(line, ",");
        int colonne = 0;
        nombreVotant++;
        while (token != NULL) {
            if (colonne > MARGE - 1 ) { //Colonne 3 = colonne des SHA 
                tableauVote->tableau[colonne - MARGE] = atoi(token);
            }
            token = strtok(NULL, ",");
            colonne++;
        }
        remplire_Matrice_Duel(*matrice,tableauVote);
    }
    delete_Tableau(tableauVote);
    fclose(file);
    return nombreVotant;
}

int lireCSVMatriceDuel(char* filename,Matrice *matrice){
    FILE *file = fopen(filename, "r");
     if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(28);
    }
    char line[MAX_LINE_LENGTH];

    // lit la premier ligne 
     if (fgets(line, MAX_LINE_LENGTH, file) == NULL){
        perror("fegts");
        exit(1);
    };
    const char *delimiteur = "\t";
    char* token = strtok(line,delimiteur);
    int nb_candidat = 0;
    while (token != NULL){
        token = strtok(NULL,delimiteur);
        nb_candidat ++;
    }
    
    *matrice = create_Matrice(nb_candidat,nb_candidat);
    init_Matrice(*matrice,0);
    
    for (int i = 0; i < (*matrice)->nb_ligne;i++){
        if (fgets(line, MAX_LINE_LENGTH, file) == NULL){
            perror("fgets");
            exit(3);
        }
        token = strtok(line, delimiteur);
        for (int j = 0 ;j < (*matrice)->nb_colonne && token != NULL;j++){
            (*matrice)->tableau[i][j] = atoi(token);
            token = strtok(NULL, delimiteur);
        }
    }
    fclose(file);
    return (*matrice)->tableau[0][1] + (*matrice)->tableau[1][0];
}
