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
    for (Element e = list_iterator_value(it) ; !list_iterator_end(it);e = list_iterator_next(it)){
        tableau->tableau[e->a]++;
    }
    list_iterator_delete(it);
}


int affichierListe(Element e,void *env){
    fprintf(env, "Candidat %d --[%d]--> Candidat %d\n", e->a, e->p, e->b);
    return 1;

}

int GraphedepoidFortnoncyclique(List *graphe, int nbSommet,ptrList * arbre) {
    // Initialiser l'ensemble disjoint
    DisjointSet *set = createDisjointSet(nbSommet);
    triee_liste_decroissant(graphe);
    printf("liste decroisante \n");
    list_reduce(graphe,&affichierListe,stdout);
    ListIterator it = list_iterator_create(graphe,FORWARD_ITERATOR);
    *arbre = list_create();
    printf("kruskal \n");
    for(Element e = list_iterator_value(it); !list_iterator_end(it); e = list_iterator_next(it) ){
        printf("\nset avant \n");
        affichierListe(e,stdout);
        printSet(set);
        if (doesCreateCycle(set, e->a, e->b)== 0) {
            printf("no create cycle\n");
            addEdge(set,e->a,e->b);
            list_push_back(*arbre,e->p,e->a,e->b);
        }else{
            printf("create cycle\n");
        }
        printSet(set);

    }
    int racine = rootThree(set);
    // Libérer la mémoire de l'ensemble disjoint
    freeDisjointSet(set);
    printf("Fin kruskal racine %d\n",racine);
    return racine;
}


int condorcet(Matrice *matriceDuel,List **graphe){   
    printf("matrice de duel\n");
    afficher_Matrice(*matriceDuel);
    *graphe = matriceDuelToGraphe(*matriceDuel);
    printf("Graphe\n");
    list_reduce(*graphe,&affichierListe,stdout);
    
    Tableau TableauScore = create_Tableau((*matriceDuel)->nb_colonne);
    init_Tableau(TableauScore,0);
    
    sommeDegresParSommet(*graphe,TableauScore);
    printf("matrice score\n");
    afficher_Tableau(TableauScore);  
    
    int colonne,valeur;

    if (max_Tableau(TableauScore,&colonne,&valeur) != 0){
       colonne = -1;
    }
    delete_Tableau(TableauScore);
    return colonne;
}


int methode_minmax(Matrice *matriceDuel){
    List *graphe = NULL;
    int vainqueur = condorcet(matriceDuel,&graphe);
    if (vainqueur == -1){
        Tableau pireScore = obtenirPiresScores(*matriceDuel);
        afficher_Tableau(pireScore);
        int valeur;
        min_Tableau(pireScore,&vainqueur,&valeur);
        delete_Tableau(pireScore);
    }
    list_delete(&graphe);
    return vainqueur;
}


int methode_paire(Matrice *matriceDuel){
    List *graphe = NULL;
    int vainqueur = condorcet(matriceDuel,&graphe);
    if (vainqueur == -1){
        List *arbre = NULL;
        vainqueur = GraphedepoidFortnoncyclique(graphe,(*matriceDuel)->nb_colonne,&arbre);
        printf("ARBRE : \n");
        list_reduce(arbre,&affichierListe,stdout);
        list_delete(&arbre);
    }
    list_delete(&graphe);
    return vainqueur;
}

int main(void)
{
    char * filename = "../Data/paire.txt";
    Matrice matriceDuel = NULL;
    int nombreElecteur = lireCSVMatriceDuel(filename,&matriceDuel);
    afficher_Matrice(matriceDuel);
    printf("nombre de votant = %d\n",nombreElecteur);
    
    int vainqueur = methode_paire(&matriceDuel);
    char * nomVainqueur = obtenir_nom_Candidat(filename,vainqueur);
    printf("Mode de paire : Condorcet paires, %d candidats, %d votants, vainqueur = %s\n",matriceDuel->nb_colonne,
    nombreElecteur,nomVainqueur);
    delete_Matrice(matriceDuel);
    free(nomVainqueur);
    
    
    return -1; //Valeur non trouvée

}
