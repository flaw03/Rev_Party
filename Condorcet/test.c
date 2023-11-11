#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LIGNES 1024
#define MAX_COLONNES 1024
#define MAX_LINE_LENGTH 1024
#define MARGE 4


#include <stdio.h>
#include <stdlib.h>
#include "utils_tab.h"


int main(int argc, char const *argv[])
{
    FILE *file = fopen("../Data/VoteCondorcet.csv", "r");
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
    afficher_Matrice(matrice);
    delete_Matrice(matrice);
    fclose(file);
	
    
    
    // Matrice matrice = create_Matrice(10,10);
    // printf("creation ok\n");
    // init_Matrice(matrice,0);
    // printf("init ok\n");
    // afficher_Matrice(matrice);
    // printf("affichage ok\n");
    // delete_Matrice(matrice);
    // printf("supression ok\n");

    
    
    return -1; //Valeur non trouvée

}
