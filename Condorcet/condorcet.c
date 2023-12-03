
#include <string.h>

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils_tab.h"
#include "lecture_csv.h"
#include "list.h"
#include "set.h"



Tableau obtenirPiresScores(Matrice matriceCombat) {
    // Vérification de la validité de la matrice de combat
    if (matriceCombat == NULL || matriceCombat->tableau == NULL) {
        fprintf(stderr, "Erreur : Matrice de combat invalide.\n");
        return NULL;  // Ou ajustez selon vos besoins
    }

    Tableau piresScores = create_Tableau(matriceCombat->nb_colonne);
    init_Tableau(piresScores, INT_MIN);

    for (int i = 0; i < matriceCombat->nb_ligne; i++) {
        for (int j = 0; j < matriceCombat->nb_colonne; j++) {
            // Comparaison pour trouver les pires scores
            if (matriceCombat->tableau[j][i] > piresScores->tableau[i]) {
                piresScores->tableau[i] = matriceCombat->tableau[j][i];
            }
        }
    }

    return piresScores;
}


// Fait la somme des degrés entrants de chaque sommet dans un graphe orienté
void sommeDegresEntrantsParSommet(List *list, Tableau tableau){
    // Vérification de la validité de la liste d'arcs
    if (list == NULL) {
        fprintf(stderr, "Erreur : Liste d'arcs invalide.\n");
        return;  // Ou ajustez selon vos besoins
    }

    ListIterator it = list_iterator_create(list, FORWARD_ITERATOR);

    // Parcours de la liste d'arcs
    for (Element e = list_iterator_value(it); !list_iterator_end(it); e = list_iterator_next(it)) {
        // Vérification de la validité des indices
        tableau->tableau[e->b]++;
        // Ajoutez d'autres vérifications si nécessaire
    }

    // Libération de l'itérateur
    list_iterator_delete(it);
}


int affichierListe(Element e,void *env){
    fprintf(env, "Candidat %d --[%d]--> Candidat %d\n", e->a, e->p, e->b);
    return 1;

}

List *matriceDuelToGraphe(Matrice matriceDuel) {
    // Vérification de la validité de la matrice de duel
    if (matriceDuel == NULL || matriceDuel->tableau == NULL) {
        fprintf(stderr, "Erreur : Matrice de duel invalide.\n");
        return NULL;  // Ou ajustez selon vos besoins
    }

    List *list = list_create();

    for (int i = 0; i < matriceDuel->nb_ligne; i++) {
        for (int j = 0; j < matriceDuel->nb_colonne; j++) {
            // Éviter les auto-arêtes (boucles)
            if (i != j) {
                // Ajouter les deux arêtes si le graphe est non orienté
                // ou ajuster selon la définition spécifique de votre problème
                if (matriceDuel->tableau[i][j] >= matriceDuel->tableau[j][i]) {
                    list_push_back(list, matriceDuel->tableau[i][j], i, j);
                    // list_push_back(list, matriceDuel->tableau[j][i], j, i);  // Ajouter l'arête inverse si nécessaire
                }
            }
        }
    }
    return list;
}


//Algorithme de Kruskal pour construire un arbre couvrant de poids maximum sans cycle dans un graphe pondéré.
int KruskalMaxWeightTree(List *graphe, int nbSommet, ptrList *arbre) {
    // Vérification de la validité de la liste
    if (graphe == NULL) {
        fprintf(stderr, "Erreur : Liste invalide.\n");
        return -1; 
    }

    // Initialiser l'ensemble disjoint
    DisjointSet *set = createDisjointSet(nbSommet);

    // Tri décroissant de la liste
    triee_liste_decroissant(graphe);
    printf("Liste décroissante :\n");
    list_reduce(graphe, &affichierListe, stdout);

    // Itération sur la liste triée
    ListIterator it = list_iterator_create(graphe, FORWARD_ITERATOR);
    *arbre = list_create();
    printf("Kruskal :\n");

    for (Element e = list_iterator_value(it); !list_iterator_end(it); e = list_iterator_next(it)) {
        printf("\nEnsemble avant :\n");
        affichierListe(e, stdout);
        printSet(set);

        if (doesCreateCycle(set, e->a, e->b) == 0) {
            printf("Pas de cycle créé.\n");
            addEdge(set, e->a, e->b);
            list_push_back(*arbre, e->p, e->a, e->b);
        } else {
            printf("Cycle créé.\n");
        }

        printSet(set);
    }

    // Trouver la racine de l'ensemble
    int racine = findRoot(set);

    // Libérer la mémoire de l'ensemble disjoint
    freeDisjointSet(set);

    printf("Fin de Kruskal. Racine : %d\n", racine);

    return racine;
}


int condorcet(Matrice matriceDuel, ptrList *graphe) {
    // Vérification de la validité de la matrice de duel
    if (matriceDuel == NULL) {
        fprintf(stderr, "Erreur : Matrice de duel invalide.\n");
        return -1; 
    }

    printf("Matrice de duel :\n");
    afficher_Matrice(matriceDuel);

    // Conversion de la matrice de duel en graphe
    *graphe = matriceDuelToGraphe(matriceDuel);
    
    // Vérification de la validité de la liste de graphe
    if (*graphe == NULL) {
        fprintf(stderr, "Erreur : Impossible de convertir la matrice de duel en graphe.\n");
        return -1; 
    }

    printf("Graphe :\n");
    list_reduce(*graphe, &affichierListe, stdout);

    // Initialisation du tableau de score
    Tableau TableauScore = create_Tableau(matriceDuel->nb_colonne);
    init_Tableau(TableauScore, 0);

    // Calcul du score selon la méthode de Condorcet
    sommeDegresEntrantsParSommet(*graphe, TableauScore);

    printf("Matrice de score :\n");
    afficher_Tableau(TableauScore);

    int colonne, valeur;

    // Recherche du maximum dans le tableau de score
    if (max_Tableau(TableauScore, &colonne, &valeur) != 0) {
        colonne = -1;
    }

    // Libération de la mémoire
    delete_Tableau(TableauScore);

    return colonne;
}



int methode_minimax(Matrice matriceDuel) {
    // Vérification de la validité de la matrice de duel
    if (matriceDuel == NULL) {
        fprintf(stderr, "Erreur : Matrice de duel invalide.\n");
        exit(3); 
    }
    List *graphe = NULL;
    int vainqueur = condorcet(matriceDuel, &graphe);


    // Vérification de la validité de la liste de graphe
    if (graphe == NULL) {
        fprintf(stderr, "Erreur : Impossible de créer la liste de graphe.\n");
        exit(4); 
    }

    if (vainqueur == -1) {
        // Obtention des pires scores en cas d'échec de la méthode de Condorcet
        Tableau pireScore = obtenirPiresScores(matriceDuel);
        afficher_Tableau(pireScore);

        int valeur;
        // Recherche du minimum dans le tableau des pires scores
        min_Tableau(pireScore, &vainqueur, &valeur);

        // Libération de la mémoire
        delete_Tableau(pireScore);
    }

    // Libération de la mémoire pour la liste de graphe
    list_delete(&graphe);

    return vainqueur;
}


int methode_paire(Matrice matriceDuel) {
    if (matriceDuel == NULL) {
        fprintf(stderr, "Erreur : Matrice de duel invalide.\n");
        exit(3); 
    }
    
    List *graphe = NULL;
    
    int vainqueur = condorcet(matriceDuel, &graphe);

    // Vérification de la validité de la matrice de duel

    // Vérification de la validité de la liste de graphe
    if (graphe == NULL) {
        fprintf(stderr, "Erreur : Impossible de créer la liste de graphe.\n");
        exit(4); 
    }

    if (vainqueur == -1) {
        List *arbre = NULL;
        vainqueur = KruskalMaxWeightTree(graphe, matriceDuel->nb_colonne, &arbre);

        // Affichage de l'arbre
        printf("ARBRE :\n");
        list_reduce(arbre, &affichierListe, stdout);

        // Libération de la mémoire pour la liste d'arbre
        list_delete(&arbre);
    }

    // Libération de la mémoire pour la liste de graphe
    list_delete(&graphe);

    return vainqueur;
}


int main(void){
    char * filename = "../Data/paire.txt";
    Matrice matriceDuel = NULL;
    int nombreElecteur;
    if (isCSV(filename)){
        nombreElecteur = lireBallot(filename,&matriceDuel);
    }else
    {
        nombreElecteur = lireMatriceDuel(filename,&matriceDuel);
    }
    
    afficher_Matrice(matriceDuel);
    printf("nombre de votant = %d\n",nombreElecteur);
    
    int vainqueur = methode_paire(matriceDuel);
    char * nomVainqueur = obtenir_nom_Candidat(filename,vainqueur);
    printf("Mode de paire : Condorcet paires, %d candidats, %d votants, vainqueur = %s\n",matriceDuel->nb_colonne,
    nombreElecteur,nomVainqueur);
    delete_Matrice(matriceDuel);
    free(nomVainqueur);
    
    
    return -1; //Valeur non trouvée

}
