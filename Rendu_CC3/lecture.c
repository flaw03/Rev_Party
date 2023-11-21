#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "Utiles.h"
#include "lecture.h"



void removeNewline(char* str) {
    size_t length = strlen(str);

    for (size_t i = 0; i < length; ++i) {
        if (str[i] == '\r' || str[i] == '\n') {
            str[i] = '\0';
        }
    }
}
int getIndiceVote(int* votes,int taille){
    int cpt = 0;
    int min = votes[0];
    for(int i = 0;i<taille;i++){
        if(votes[i]<min && votes[i] != -1){
            cpt=i;
            min = votes[i];
        }
    }
    return cpt;
}

Candidat* candidatAssocie(int nb,ListCand* lstCand){
    assert(nb<=lstCand->size);
    Candidat* candidat = lstCand->head;
    for(int i = 0;i<nb;i++){
        candidat = candidat->next;
    }
    return candidat;
}


ListElect* getElecteur(ListElect* lstElect,ListCand* lstCand,char* fichier,int* tab) {
    FILE* file = fopen(fichier, "r");
    if (file == NULL) {
        perror("Impossible d'ouvrir le fichier");
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
            if (colonneActuelle == colonneID) {
                nom = strdup(token);
            }
            else if (colonneActuelle == colonneNom) {
                prenom = strdup(token);
                removeNewline(prenom);
            }
            else if (colonneActuelle >= colonneVote) {
                int x = atoi(token);
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
        perror("Impossible d'ouvrir le fichier");
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

int* indice(ListCand* candidats, char* fichier, int* tab) {
    int nb1 = -1; // Initialize to a value not possible in your context
    int nb2 = -1; // Initialize to a value not possible in your context

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
                    if (strcmp(candidats->head->prenom, nom) == 0) {
                        nb1 = colonneActuelle;
                    }
                    if (strcmp(candidats->tail->prenom, nom) == 0) {
                        nb2 = colonneActuelle;
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

    tab[0] = nb1;
    tab[1] = nb2;
    return tab;
}


int getIndice(Candidat* candidats, char* fichier) {
    int nb1 = -1; // Initialize to a value not possible in your context
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

ListElect* electeurs2ndTours2Candidats(ListElect* lstElect,Candidat* c1,Candidat* c2,char* fichier) {
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
            else if (colonneActuelle == indiceC1) {
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
        free(nom);
        free(prenom);

    }
    fclose(file);
    return lstElect;
    
}


ListElect* getElecteur2ndTour(ListElect* lstElect,ListCand* lstCand,char* fichier,int* tab) {
    FILE* file = fopen(fichier, "r");
    if (file == NULL) {
        perror("Impossible d'ouvrir le fichier");
        exit(1);
    }
    char line[MAX_LINE_LENGTH];
    int cpt = 0;
    int premiereLigne = 1;
    int votesFinalistes[2] = {0, 0};
    indice(lstCand,fichier,votesFinalistes);
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
            else if (colonneActuelle == votesFinalistes[0]) {
                int x = atoi(token);
                tab[cpt] = x;
                cpt++;
            }
            else if (colonneActuelle == votesFinalistes[1]) {
                int x = atoi(token);
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




// int main(int argc, char** argv) {
    // if(argc<2){
    //     fprintf(stderr,"Erreur USAGE [%s] mauvais nombre d'arguments\n",argv[0]);
    //     exit(1);
    // }

    // ListCand* lstCand = listCand_create();
    // ListElect* lstElect = listElect_create();
    // lstCand = getCandidat(lstCand,argv[1]);
    // int nb = lstCand->size;
    // int tab[nb];
    // lstElect = getElecteur(lstElect,lstCand,argv[1],tab);

    // for(Electeur *e = lstElect->head;e!=NULL;e = e->next){
    //     printf("Electeur : %s %s a voté pour %s\n",e->nom,e->prenom,e->candidat->prenom);
    // }

    // printf("\n");


    // printList(lstCand);


    // listCand_delete(lstCand);
    // listElect_delete(lstElect);
    // Candidat* c1 = create_candidat("Clafouti", "Clafouti", 10);
    // Candidat* c2 = create_candidat("Tarte à la fraise", "Tarte à la fraise", 12);
    // ListCand* finalistes = listCand_create();
    // listCand_add(finalistes,c1);
    // listCand_add(finalistes,c2);
    // int index[2] = {0, 0};
    // indice(finalistes, "vote10.csv", index);
    // printf("index = %d %d\n", index[0], index[1]);

    // ListElect* electeurs2 = listElect_create();
    // int tab[finalistes->size];
    // getElecteur2ndTour(electeurs2,finalistes,"vote10.csv",tab);

    //  for(Electeur *e = electeurs2->head;e!=NULL;e = e->next){
    //     printf("Electeur : %s %s a voté pour %s\n",e->nom,e->prenom,e->candidat->prenom);
    // }



    // listCand_delete(finalistes);
    // listElect_delete(electeurs2);

//     Candidat* c1 = create_candidat("Clafouti","Clafouti",28);
//     Candidat* c2 = create_candidat("Tarte à la fraise","Tarte à la fraise",36);
//     ListElect *l = listElect_create();
//     testElecteur(l,c1,c2,"vote10.csv");

//     for(Electeur* e = l->head;e!=NULL;e=e->next){
//         printf("%s a voté pour %s\n",e->prenom,e->candidat->prenom);
//     }

//     printf("C1 = %d\nC2 = %d\n",c1,c2);

//     listElect_delete(l);
//     free(c1->nom);
//     free(c1->prenom);
//     free(c1);
//     free(c2->nom);
//     free(c2->prenom);
//     free(c2);


    


//     return 0;
// }

