#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
void sommeDegresSortantParSommet(List *list, Tableau tableau){
    // Vérification de la validité de la liste d'arcs
    if (list == NULL) {
        fprintf(stderr, "Erreur : Liste d'arcs invalide.\n");
        return;  // Ou ajustez selon vos besoins
    }

    ListIterator it = list_iterator_create(list, FORWARD_ITERATOR);

    // Parcours de la liste d'arcs
    for (Element e = list_iterator_value(it); !list_iterator_end(it); e = list_iterator_next(it)) {
        // Vérification de la validité des indices
        tableau->tableau[e->a]++;
        // Ajoutez d'autres vérifications si nécessaire
    }

    // Libération de l'itérateur
    list_iterator_delete(it);
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


int afficherArc(Element e,void *env){
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
                    list_push_back(list, matriceDuel->tableau[i][j] -matriceDuel->tableau[j][i] , i, j);
                    // list_push_back(list, matriceDuel->tableau[j][i], j, i);  // Ajouter l'arête inverse si nécessaire
                }
            }
        }
    }
    return list;
}


//Algorithme de Kruskal pour construire un arbre couvrant de poids maximum sans cycle dans un graphe pondéré.
int KruskalMaxWeightTree(List *graphe, int nbSommet,FILE* logfile) {
    // Vérification de la validité de la liste
    if (graphe == NULL) {
        fprintf(stderr, "Erreur : Liste invalide.\n");
        return -1; 
    }
    // Initialiser l'ensemble disjoint

    // Tri décroissant de la liste
    triee_liste_decroissant(graphe);
    fprintf(logfile,"Liste décroissante :\n");
    list_reduce(graphe, &afficherArc, logfile);

    // Itération sur la liste triée
    ListIterator it = list_iterator_create(graphe, FORWARD_ITERATOR);
    ptrList arbre = list_create();

    DisjointSet *set = createDisjointSet(nbSommet);
    fprintf(logfile,"\nEnsemble :\n");
    printSet(set,logfile);

    fprintf(logfile,"Kruskal :\n");
    for (Element e = list_iterator_value(it); !list_iterator_end(it); e = list_iterator_next(it)) {
        
        fprintf(logfile,"\nArc courrant\n");
        afficherArc(e, stdout);

        if (doesCreateCycle(set, e->a, e->b) == 0) {
            fprintf(logfile,"Pas de cycle créé.\n");
            addEdge(set, e->a, e->b);
            list_push_back(arbre, e->p, e->a, e->b);
        } else {
            fprintf(logfile,"Cycle créé.\n");
        }

        fprintf(logfile,"\nEnsemble :\n");
        printSet(set,logfile);
    }
    // Afficher l'arbre trouvé
    fprintf(logfile,"\nARBRE :\n");
    list_reduce(arbre, &afficherArc, stdout);

    // Trouver la racine de l'ensemble
    int racine = findRoot(set);

    // Libérer la mémoire de l'ensemble disjoint
    freeDisjointSet(set);

    list_delete(&arbre);

    fprintf(logfile,"\nFin de Kruskal. Racine : %d\n", racine);

    return racine;
}


int resolutionSchulze(ptrList graphe,int nbCandidat,FILE* logfile) {
    int vainqueur;
    Tableau tableauArcEntrant = create_Tableau(nbCandidat);
    init_Tableau(tableauArcEntrant, 0);

    // Calcul des scores entrants
    sommeDegresEntrantsParSommet(graphe, tableauArcEntrant);

    // Affichage du graphe

    // Affichage du tableau de scores entrants
    fprintf(logfile,"\nTableau de scores entrants :\n");
    afficher_Tableau(tableauArcEntrant,logfile);

    // Tri décroissant du graphe
    triee_liste_decroissant(graphe);

    // Affichage du graphe trié
    ListIterator it = list_iterator_create(graphe, BACKWARD_ITERATOR);
    fprintf(logfile,"\nGraphe trié :\n");
    for (Element e = list_iterator_value(it); !list_iterator_end(it); e = list_iterator_next(it)) {
        afficherArc(e, stdout);
    }

    // Itération sur le graphe trié pour déterminer le vainqueur
    int valeur;
    min_Tableau(tableauArcEntrant, &vainqueur, &valeur);
    list_iterator_begin(it);
    for (Element e = list_iterator_value(it); valeur > 0; e = list_iterator_next(it)) {
        fprintf(logfile,"\nArc courrant\n");
        afficherArc(e, stdout);
        fprintf(logfile,"Tableau de scores après la réduction :\n");
        afficher_Tableau(tableauArcEntrant,logfile);
        tableauArcEntrant->tableau[e->b]--;
        min_Tableau(tableauArcEntrant, &vainqueur, &valeur);
    }

    // Affichage final du tableau de scores
    fprintf(logfile,"\nTableau de scores entrants :\n");
    afficher_Tableau(tableauArcEntrant,logfile);

    // Libération de la mémoire
    delete_Tableau(tableauArcEntrant);
    // Libération de la mémoire pour la liste d'arbre
    list_iterator_delete(it);
    return vainqueur;
}

int condorcet(Matrice matriceDuel, ptrList *graphe,FILE* logfile) {
    // Vérification de la validité de la matrice de duel
    if (matriceDuel == NULL) {
        fprintf(stderr, "Erreur : Matrice de duel invalide.\n");
        return -1; 
    }

    fprintf(logfile,"\nMatrice de duel :\n");
    afficher_Matrice(matriceDuel,logfile);

    // Conversion de la matrice de duel en graphe
    *graphe = matriceDuelToGraphe(matriceDuel);
    
    // Vérification de la validité de la liste de graphe
    if (*graphe == NULL) {
        fprintf(stderr, "Erreur : Impossible de convertir la matrice de duel en graphe.\n");
        return -1; 
    }

    fprintf(logfile,"\nGraphe :\n");
    list_reduce(*graphe, &afficherArc, stdout);

    // Initialisation du tableau de score
    Tableau tableauArcSortant = create_Tableau(matriceDuel->nb_colonne);
    init_Tableau(tableauArcSortant, 0);

    // Calcul du score selon la méthode de Condorcet
    sommeDegresSortantParSommet(*graphe, tableauArcSortant);

    fprintf(logfile,"\nTableau de score des arcs Sortant :\n");
    afficher_Tableau(tableauArcSortant,logfile);

    int colonne, valeur;

    // Recherche du maximum dans le tableau de score
    if (max_Tableau(tableauArcSortant, &colonne, &valeur) != 0) {
        fprintf(logfile, "Aucun vainqueur de Condorcet trouvé.\n");
        colonne = -1;
    }

    // Libération de la mémoire
    delete_Tableau(tableauArcSortant);

    return colonne;
}



int methode_Minimax(Matrice matriceDuel,FILE* logfile) {
    // Vérification de la validité de la matrice de duel
    if (matriceDuel == NULL) {
        fprintf(stderr, "Erreur : Matrice de duel invalide.\n");
        exit(3); 
    }
    List *graphe = NULL;
    int vainqueur = condorcet(matriceDuel, &graphe,logfile);


    // Vérification de la validité de la liste de graphe
    if (graphe == NULL) {
        fprintf(stderr, "Erreur : Impossible de créer la liste de graphe.\n");
        exit(4); 
    }

    if (vainqueur == -1) {
        // Obtention des pires scores en cas d'échec de la méthode de Condorcet
        fprintf(logfile,"\n-- Resoltion du conflit avec la methode minimax --\n");
        Tableau pireScore = obtenirPiresScores(matriceDuel);
        fprintf(logfile,"\nTableau des pire defaites de chaque Candidats\n");
        afficher_Tableau(pireScore,logfile);

        int valeur;
        // Recherche du minimum dans le tableau des pires scores
        if (min_Tableau(pireScore, &vainqueur, &valeur) == 1){
            vainqueur = -1;
            fprintf(logfile, "ERREUR : Il y a des doublons dans le tableau des pires scores.\n");
        }else{
            fprintf(logfile,"\nVainqueur apres Resoltion du conflit avec la methode minimax : %d\n",vainqueur);
        }
        

        // Libération de la mémoire
        delete_Tableau(pireScore);
    }

    // Libération de la mémoire pour la liste de graphe
    list_delete(&graphe);

    return vainqueur;
}


int methode_Rangement_Des_Paires(Matrice matriceDuel,FILE* logfile) {
    if (matriceDuel == NULL) {
        fprintf(stderr, "Erreur : Matrice de duel invalide.\n");
        exit(3); 
    }
    
    List *graphe = NULL;
    
    int vainqueur = condorcet(matriceDuel, &graphe,logfile);

    // Vérification de la validité de la liste de graphe
    if (graphe == NULL) {
        fprintf(stderr, "Erreur : Impossible de créer la liste de graphe.\n");
        exit(4); 
    }

    if (vainqueur == -1) {
        fprintf(logfile,"\n-- Resoltion du conflit avec la methode rangement des paires par ordre décroissant --\n");
        vainqueur = KruskalMaxWeightTree(graphe, matriceDuel->nb_colonne,logfile);
        fprintf(logfile,"\nVainqueur apres Resoltion du conflit avec la methode rangement des paires par ordre décroissant : %d\n",vainqueur);
    }

    // Libération de la mémoire pour la liste de graphe
    list_delete(&graphe);

    return vainqueur;
}

int methode_Schulze(Matrice matriceDuel,FILE* logfile){
    if (matriceDuel == NULL) {
        fprintf(stderr, "Erreur : Matrice de duel invalide.\n");
        exit(3); 
    }
    
    List *graphe = NULL;
    int vainqueur = condorcet(matriceDuel, &graphe,logfile);

    // Vérification de la validité de la liste de graphe
    if (graphe == NULL) {
        fprintf(stderr, "Erreur : Impossible de créer la liste de graphe.\n");
        exit(4); 
    }
    if (vainqueur == -1){
        fprintf(logfile,"\n-- Resoltion du conflit avec Schulze --\n");
        vainqueur = resolutionSchulze(graphe,matriceDuel->nb_colonne,logfile);
        fprintf(logfile,"\nVainqueur apres Resoltion du conflit avec Schulze : %d\n",vainqueur);
    }
    list_delete(&graphe);
    return vainqueur;
}


int main(void){
    char * filename = "../Data/vote100.csv";
    bool isBallot = false;
    Matrice matriceDuel = NULL;
    int nombreElecteur;
    FILE * logfile = stdout;
    if (isBallot){
        nombreElecteur = lireBallot(filename,&matriceDuel);
    }else
    {
        nombreElecteur = lireMatriceDuel(filename,&matriceDuel);
    }
    
    
    int vainqueur = methode_Minimax(matriceDuel,logfile);
    char * nomVainqueur = obtenir_nom_Candidat(filename,vainqueur,isBallot);
    fprintf(logfile,"Mode de paire : Condorcet paires, %d candidats, %d votants, vainqueur = %s\n",matriceDuel->nb_colonne,
    nombreElecteur,nomVainqueur);
    delete_Matrice(matriceDuel);
    free(nomVainqueur);
    
    
    return -1; //Valeur non trouvée

}
