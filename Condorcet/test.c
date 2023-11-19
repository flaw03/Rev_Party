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

int Condorcet(char *filenmae,Matrice *matriceCombat,List **graphe,int * nombreElecteur){   
    *nombreElecteur = lireCSVCondorcet(filenmae,&matriceCombat);
    afficher_Matrice(matriceCombat);
    printf("df\n");
    int colonne;
    int valeur;
    Matrice m2 = create_Matrice(1,(*matriceCombat)->nb_colonne);
    graphe = matriceCombatToGraphe(matriceCombat);
    list_reduce(graphe,&f);
    init_Matrice(m2,0);
    Vainquqeur(graphe,m2);
    afficher_Matrice(m2);
    if (max_Matrice_Ligne(m2,&colonne,&valeur) == 0){
       return colonne;
    }
    else{
        return -1;
    }
}


void methode_minmax(char *filenmae){
    Matrice matriceCombat = NULL;
    List *graphe = NULL;
    int nombreElecteur;
    int vainqueur = Condorcet(filenmae,matriceCombat,graphe,&nombreElecteur);
    if (vainqueur == -1){
        Matrice pireScore = obtenirPiresScores(matriceCombat);
        afficher_Matrice(pireScore);
        int ligne,valeur;
        min_Matrice(pireScore,&ligne ,&vainqueur,&valeur);
    }
    printf("Mode de scrutin : Condorcet minimax, %d candidats, %d votants, vainqueur = %s",matriceCombat->nb_colonne,
    nombreElecteur,obtenir_nom_Candidat(filenmae,vainqueur));
}


int main(void)
{
    methode_minmax("../Data/VoteCondorcet.csv");
    
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
