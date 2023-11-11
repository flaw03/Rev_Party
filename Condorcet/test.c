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
#include "lecture_csv.h"


int main(void)
{

    Matrice matrice = lireCSVCondorcet("../Data/VoteCondorcet.csv");
    afficher_Matrice(matrice);
    delete_Matrice(matrice);
    
    
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
