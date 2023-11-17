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
#include "list.h"

int f(int a , int  b,int p){
    printf(" Candidat %d --[%d]--> candidat %d\n",a,p,b);
    return 1;
}


int main(void)
{

    Matrice matrice = lireCSVCondorcet("../Data/testCondorcet.csv");
    afficher_Matrice(matrice);
    List *liste = matriceCombatToGraphe(matrice);
    list_reduce(liste,&f);
    Matrice m2 = create_Matrice(1,matrice->nb_colonne);
    init_Matrice(m2,0);
    int v = Vainqueur(liste,m2);
    printf("Le vainqueur du vote de Condorcet est %d\n",v);
    list_delete(&liste);
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
