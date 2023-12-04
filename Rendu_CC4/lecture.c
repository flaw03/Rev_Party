#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "../Rendu_CC4/fichiers.h/Utiles.h"
#include "../Rendu_CC4/fichiers.h/lecture.h"



void removeNewline(char* str) {
    size_t length = strlen(str);

    for (size_t i = 0; i < length; ++i) {
        if (str[i] == '\r' || str[i] == '\n') {
            str[i] = '\0';
        }
    }
}




ListElect* getElecteur(ListElect* lstElect,ListCand* lstCand,char* fichier,int* tab) {
    FILE* file = fopen(fichier, "r");
    if (file == NULL) {
        perror("Impossible d'ouvrir le fichier!!");
        exit(1);
    }
    char line[MAX_LINE_LENGTH];
    int cpt = 0;
    int premiereLigne = 1;


    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (premiereLigne) {
            premiereLigne = 0;  // Ignorer la première ligne
            continue;
        }

        int colonneActuelle = 0;
        char* token = strtok(line, ",");
        char* nom = NULL;
        char* prenom = NULL;

        while (token != NULL) {
            if (colonneActuelle == colonneID) { //Association ID au nom
                nom = strdup(token);
            }
            else if (colonneActuelle == colonneNom) {// Association NOM au prenom
                prenom = strdup(token);
                removeNewline(prenom);
            }
            else if (colonneActuelle >= colonneVote) { // Récupération de chaque vote , si vote non comptabilisé => pire valeur
                int x = atoi(token);
                if(x==-1){
                    x=10;
                }
                tab[cpt] = x;
                cpt++;
        

            }

            token = strtok(NULL, ",");
            colonneActuelle++;
        }
            cpt = 0;
            int voteCandidat = getIndiceVote(tab,lstCand->size);
            Candidat* candidat = candidatAssocie(voteCandidat,lstCand);
            Electeur* e = create_electeur(nom,prenom,candidat);
            list_add_Electeur(lstElect,e);
        
        free(nom);
        free(prenom);

    }
    fclose(file);
    return lstElect;
    
}

ListCand* getCandidat(ListCand* lstCand,char* fichier){
    srand(time(NULL));
    FILE* file = fopen(fichier, "r");
    if (file == NULL) {
        perror("Impossible d'ouvrir le fichier dans getCandidat");
        exit(1);
    }
    char line[MAX_LINE_LENGTH];
    int firstline = 0;
    // Lire chaque ligne du fichier CSV
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if(firstline == 0){ 
        char* token = strtok(line, ",");
        int colonneActuelle = 0;

        // Parcourir les tokens (colonnes)
        while (token != NULL) {
            // Si nous avons atteint la colonne souhaitée, l'afficher
            if (colonneActuelle >= colonneVote) {
                char* nom = strdup(token);
                removeNewline(nom);
                int nb = rand()%60+20; //Créer un age aléatoire pour vote uninominal
                Candidat* c = create_candidat(nom,nom,nb); //Données manquantes pour le nom et prénom => désignation = 2x prenom
                listCand_add(lstCand,c);
                free(nom);
            }

            // Obtenir le prochain token
            token = strtok(NULL, ",");
            colonneActuelle++;
        }
        firstline = 1;
        fclose(file);
        return lstCand;
    }
    }
    return NULL;
}



int getIndice(Candidat* candidats, char* fichier) {
    int nb1 = -1; // Initialize to a value not possible in the context
    FILE* file = fopen(fichier, "r");
    if (file == NULL) {
        perror("Impossible d'ouvrir le fichier");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int firstline = 0;

    // Lire chaque ligne du fichier CSV
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (firstline == 0) {
            char* token = strtok(line, ",");
            int colonneActuelle = 0;

            // Parcourir les tokens (colonnes)
            while (token != NULL) {
                // Si nous avons atteint la colonne souhaitée, l'afficher
                if (colonneActuelle >= colonneVote) {
                    char* nom = strdup(token);
                    removeNewline(nom);
                    if (strcmp(candidats->prenom, nom) == 0) {
                        nb1 = colonneActuelle;
                    }
                    free(nom);
                }

                // Obtenir le prochain token
                token = strtok(NULL, ",");
                colonneActuelle++;
            }
            firstline = 1;
        }
    }

    fclose(file);

    return nb1;
}

ListElect* electeurs2ndTours2Candidats(ListElect* lstElect,Candidat* c1,Candidat* c2,char* fichier,FILE* logfile) {
    FILE* file = fopen(fichier, "r");
    if (file == NULL) {
        perror("Impossible d'ouvrir le fichier");
        exit(1);
    }
    char line[MAX_LINE_LENGTH];
    int tab[2] = {0,0};
    int cpt = 0;
    int premiereLigne = 1;
    int indiceC1 = getIndice(c1,fichier);
    int indiceC2 = getIndice(c2,fichier);
    fprintf(logfile,"\n\nVERIF 2ND TOUR : \n");
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (premiereLigne) {
            premiereLigne = 0;  // Ignorer la première ligne
            continue;
        }

        int colonneActuelle = 0;
        char* token = strtok(line, ",");
        char* nom = NULL;
        char* prenom = NULL;

        while (token != NULL) {
            if (colonneActuelle == colonneID) {
                nom = strdup(token);
            }
            else if (colonneActuelle == colonneNom) {
                prenom = strdup(token);
                removeNewline(prenom);
            }
            else if (colonneActuelle == indiceC1) {//Recupère seulement les votes des candidats C1 et C2
                int x = atoi(token);
                tab[cpt] = x;
                cpt++;
            }
            else if (colonneActuelle == indiceC2) {
                int x = atoi(token);
                tab[cpt] = x;
                cpt++;
            }

            token = strtok(NULL, ",");
            colonneActuelle++;
        }
        cpt = 0;
        Candidat* candidat;
        if(tab[0]<=tab[1]){
            candidat = c1;
        }
        else{
            candidat = c2;
        }
        candidat->vote++;
        Electeur* e = create_electeur(nom,prenom,candidat);
        list_add_Electeur(lstElect,e);
        fprintf(logfile,"Electeur : %s %s a voté pour %s\n",e->nom,e->prenom,e->candidat->prenom);
        free(nom);
        free(prenom);

    }
    fclose(file);
    return lstElect;
    
}


void initJugement(ListCand* lstCand,ListElect* lstElect,char* fichier) {
    FILE* file = fopen(fichier, "r");
    if (file == NULL) {
        perror("Impossible d'ouvrir le fichier!!");
        exit(1);
    }
    int taille = lstElect->size;
    createTableau(taille,lstCand); //Alloue de la mémoire à tous les tableaux de chaque candidats
    
    int cpt = 0;
    char line[MAX_LINE_LENGTH];
    int premiereLigne = 1;
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (premiereLigne) {
            premiereLigne = 0;  // Ignorer la première ligne
            continue;
        }
        int colonneActuelle = 0;
        char* token = strtok(line, ",");
        Candidat* candidat = lstCand->head;
        while (token != NULL) { 
           if(colonneActuelle>=colonneVote){
            int x = atoi(token);
            if(x==-1){
                x=10;
            }
            candidat->jugement[cpt] = x; //Récupère tous les votes pour un candidat et les insère dans le tableau de ce candidat
            candidat = candidat->next;
           }
            token = strtok(NULL, ",");
            colonneActuelle++;
        }
        candidat = lstCand->head;
        cpt++;
    }


    fclose(file);
}


