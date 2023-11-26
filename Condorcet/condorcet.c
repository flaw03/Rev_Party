#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <stdio.h>
#include <stdlib.h>
#include "utils_tab.h"
#include "lecture_csv.h"
#include "list.h"
#include "set.h"

// Fait la somme des de chaque sommet 
void sommeDegresParSommet(List * list,Tableau tableau){
    ListIterator it = list_iterator_create(list,FORWARD_ITERATOR);
    for (Element e = list_iterator_next(it) ; !list_iterator_end(it);e = list_iterator_next(it)){
        tableau->tableau[e->a]++;
    }
    list_iterator_delete(it);
}



int kruskal(List *graphe, int nbSommet,List * arbre) {
    // Initialiser l'ensemble disjoint
    DisjointSet *set = createDisjointSet(nbSommet);
    triee_liste_decroissant(graphe);
    ListIterator it = list_iterator_create(graphe);
    arbre = list_create();
    for(Element e = list_iterator_next(it); !list_iterator_end(it); e = list_iterator_next(it) ){
        if (!doesCreateCycle(set, e->a, e->b)) {
            unionSets(set, e->a, e->b);
            list_push_back(arbre,e->p,e->a,e->b);
        }
    }
    // Libérer la mémoire de l'ensemble disjoint
    int racine = rootThree(set)
    freeDisjointSet(set);
    return racine;
}

int affichierListe(Element e,void *env){
    fprintf(env, "Candidat %d --[%d]--> Candidat %d\n", e->a, e->p, e->b);
    return 1;

}

int condorcet(char *filenmae,Matrice *matriceCombat,List **graphe,int * nombreElecteur){   
    *nombreElecteur = lireCSVCondorcet(filenmae,matriceCombat);
    afficher_Matrice(*matriceCombat);
    *graphe = matriceCombatToGraphe(*matriceCombat);
    list_reduce(*graphe,&affichierListe,stdout);
    
    Tableau TableauScore = create_Tableau((*matriceCombat)->nb_colonne);
    init_Tableau(TableauScore,0);
    
    sommeDegresParSommet(*graphe,TableauScore);
    afficher_Tableau(TableauScore);  
    
    int colonne,valeur;

    if (max_Tableau(TableauScore,&colonne,&valeur) != 0){
       colonne = -1;
    }
    delete_Tableau(TableauScore);
    return colonne;
}


void methode_minmax(char *filenmae){
    Matrice matriceCombat = NULL;
    List *graphe = NULL;
    int nombreElecteur;
    int vainqueur = condorcet(filenmae,&matriceCombat,&graphe,&nombreElecteur);
    if (vainqueur == -1){
        Tableau pireScore = obtenirPiresScores(matriceCombat);
        afficher_Tableau(pireScore);
        int valeur;
        min_Tableau(pireScore,&vainqueur,&valeur);
        delete_Tableau(pireScore);
    }
    char * nomVainqueur = obtenir_nom_Candidat(filenmae,vainqueur);
    printf("Mode de scrutin : Condorcet minimax, %d candidats, %d votants, vainqueur = %s\n",matriceCombat->nb_colonne,
    nombreElecteur,nomVainqueur);
    free(nomVainqueur);
    delete_Matrice(matriceCombat);
    list_delete(&graphe);
}


void methode_paire(char *filenmae){
    Matrice matriceCombat = NULL;
    List *graphe = NULL;
    int nombreElecteur;
    int vainqueur = condorcet(filenmae,&matriceCombat,&graphe,&nombreElecteur);
    if (vainqueur == -1){
        List *arbre = NULL;
        vainqueur = kruskal(graphe,matriceCombat->nb_colonne,arbre);
        list_delete(&arbre);
        }
    char * nomVainqueur = obtenir_nom_Candidat(filenmae,vainqueur);
    printf("Mode de paire : Condorcet paires, %d candidats, %d votants, vainqueur = %s\n",matriceCombat->nb_colonne,
    nombreElecteur,nomVainqueur);
    free(nomVainqueur);
    delete_Matrice(matriceCombat);
    list_delete(&graphe);
}

int main()
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
