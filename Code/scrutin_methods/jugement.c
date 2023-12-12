#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "../utility_module/utiles.h"
#include "../utility_module/lecture_csv.h"
#include "../utility_module/utils_tab.h"
#include "jugement.h"


// Fonction pour trier les classements de chaque candidat par ordre décroissant
void trierVotes(ListCand* lstCand) {
    for (Candidat* c = lstCand->head; c != NULL; c = c->next) {
        trier_Tableau(c->jugement);
    }
}

// Fonction pour associer une valeur de mention avec sa distance correspondante
int assocMention(int i) {
    int retour = 0;
    if (i == 1 || i == 3 || i == 5 || i == 7 || i == 9) {
        retour = 1;
    } else if (i == 2 || i == 4 || i == 6 || i == 8) {
        retour = 2;
    }
    return retour;
}

// Fonction pour calculer le chemin à partir d'un tableau de classements
int calculerChemin(Tableau tab) {
    int mid;
    if (tab->dim % 2 == 0) {
        mid = (tab->dim / 2) - 1;
    } else {
        mid = tab->dim / 2;
    }
    int mention = tab->tableau[mid]; // médiane
    int addMention = assocMention(mention); // distance jusqu'à la prochaine mention
    int cpt = 0;
    int recherche = mention + addMention;

    while (mention < recherche || cpt == tab->dim) {
        mid--;
        mention = tab->tableau[mid];
        cpt++;
    }
    return cpt;
}

// Fonction pour calculer la médiane d'un tableau d'entiers
double mediane(Tableau tab) {
    int verif = tab->dim % 2;
    if (verif == 0) {
        int mid = (tab->dim / 2) - 1;
        return tab->tableau[mid];
    } else {
        int mil = (tab->dim / 2);
        return tab->tableau[mil];
    }
}


// Fonction pour afficher les détails d'un candidat (vote, médiane)
void affichage(FILE* logfile, Candidat* c) {
    fprintf(logfile, "Candidat : %s\nvotes : ", c->prenom);
    afficherVote(c->jugement, logfile);
    fprintf(logfile, "\nMediane : %f\n\n", mediane(c->jugement));
}

// Fonction pour gérer le cas des chemins égaux entre deux candidats
void gererCasCheminsEgaux(Candidat* gagnant, Candidat* candidatCourant) {
    int cheminGagnantv2, cheminCourantv2;
    double med1, med2;

    do {
        gagnant->jugement->dim--; //Passe au vote de l'électeur d'avant (tableau rangé ordre décroissant)
        cheminGagnantv2 = calculerChemin(gagnant->jugement); //Recalcule le chemin sans cet electeur
        cheminCourantv2 = calculerChemin(candidatCourant->jugement);//Recalcule le chemin sans cet electeur
        med1 = mediane(gagnant->jugement);//Recalcule la mediane sans cet electeur
        med2 = mediane(candidatCourant->jugement);//Recalcule la mediane sans cet electeur
    } while (med1 == med2 && cheminCourantv2 == cheminGagnantv2); //Jusqu'à trouver une médiane et/ou une distance de chemin différente

    if (cheminCourantv2 > cheminGagnantv2 || (med2 < med1 && cheminCourantv2 != cheminGagnantv2)) {
        gagnant = candidatCourant;
    }
}

// Fonction principale pour le jugement majoritaire
Candidat* jugementMajoritaire(ListCand* lstCand, ListElect* lstElect, char* fichier, FILE* logfile) {
    initJugement(lstCand, lstElect, fichier);
    trierVotes(lstCand);
    Candidat* gagnant = lstCand->head;
    double medianeGagnant = mediane(gagnant->jugement);
    fprintf(logfile, "\n\nDEBUT VERIFICATION JUGEMENT MAJORITAIRE\n\n");
    affichage(logfile,gagnant);
    // Comparaison de tous les candidats et de leur médiane, en prenant celui avec la médiane la plus basse (meilleure mention)
    for (Candidat* c = lstCand->head->next; c != NULL; c = c->next) {
        affichage(logfile,c);
        double medianeEtudiee = mediane(c->jugement);

        if (medianeEtudiee < medianeGagnant) {
            medianeEtudiee = medianeGagnant;
            gagnant = c;
        }
        // Égalité entre deux médianes => Calculer le chemin jusqu'à la prochaine pire mention obtenue
        else if (medianeEtudiee == medianeGagnant) {
            int cheminGagnant = calculerChemin(gagnant->jugement);
            int cheminCandCourant = calculerChemin(c->jugement);

            if (cheminCandCourant > cheminGagnant || (cheminCandCourant == cheminGagnant && medianeEtudiee < medianeGagnant)) {
                gagnant = c;
                medianeGagnant = medianeEtudiee;
            } else if (cheminCandCourant == cheminGagnant) {
                //Égalité entre deux médianes et deux distances => passer à la prochaine mention et recalculer la distance jusqu'à la prochaine pire mention
                gererCasCheminsEgaux(gagnant, c);
            }
        }
    }

    fprintf(logfile, "Fin. Candidat majoritairement élu est : %s", gagnant->prenom);
    return gagnant;
}

// Fonction pour effectuer le vote par jugement majoritaire
void voteJugementMajoritaireBallot(char* fichier, FILE* logfile) {
    fprintf(logfile, "---------------------------------------------------------------\n");
    fprintf(logfile, "Methode Jugement Majoritaire\n");
    ListCand* lstCand = listCand_create();
    ListElect* lstElect = listElect_create();
    getCandidat(lstCand, fichier);
    Tableau tab = create_Tableau(lstCand->size);
    lstElect = getElecteur(lstElect, lstCand, fichier, tab);

    Candidat* gagnant = jugementMajoritaire(lstCand, lstElect, fichier, logfile);
    printf("Mode de Scrutin : Jugement majoritaire %d candidats, %d votants, Vainqueur = %s\n", lstCand->size, lstElect->size, gagnant->prenom);

    delete_Tableau(tab);
    listCand_delete(lstCand);
    listElect_delete(lstElect);
}
