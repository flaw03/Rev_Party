#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

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
    if((unsigned int)nb>lstCand->size){
    	fprintf(stderr,"Indice candidat invalide");
    	exit(18);
    }
    Candidat* candidat = lstCand->head;
    for(int i = 0;i<nb;i++){
        candidat = candidat->next;
    }
    return candidat;
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
            if (colonneActuelle == colonneID) {
                nom = strdup(token);
            }
            else if (colonneActuelle == colonneNom) {
                prenom = strdup(token);
                removeNewline(prenom);
            }
            else if (colonneActuelle >= colonneVote) {
                int x = atoi(token);
                if(x==-1){
                    x=0;
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
        fprintf(logfile,"Electeur : %s %s a voté pour %s\n",e->nom,e->prenom,e->candidat->prenom);
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

void createTableau(int taille,ListCand* lstCand){
    for(Candidat* c = lstCand->head;c!=NULL;c = c->next){
        c->jugement = malloc(taille*sizeof(int));
    }
}

void initJugement(ListCand* lstCand,ListElect* lstElect,char* fichier) {
    FILE* file = fopen(fichier, "r");
    if (file == NULL) {
        perror("Impossible d'ouvrir le fichier!!");
        exit(1);
    }
    int taille = lstElect->size;
    createTableau(taille,lstCand);
    
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
                x=0;
            }
            candidat->jugement[cpt] = x;
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



// void trier(int* tab,int taille){
//     for(int i = 0;i<taille;i++){
//         for(int j = 0;j<taille;j++){
//             if(tab[i]>tab[j]){
//                 int temp = tab[i];
//                 tab[i] = tab[j];
//                 tab[j] = temp;
//             }
//         }
//     }

// }

// void trierVotes(ListCand* lstCand,int taille){
//     for(Candidat* c = lstCand->head;c!=NULL;c = c->next){
//         trier(c->jugement,taille);
//     }
// }

// double moyenne(int* tab,int taille){
//     double moy=0;
//     for(int i = 0;i<taille;i++){
//         moy+= tab[i];
//     }
//     return moy/taille;
// }

// double mediane(int* tab,int taille){
//     int verif = taille%2;
//     if(verif == 0){
//         int mid = (taille/2)-1;
//         return tab[mid];
//     }
//     else{
//         printf("odd");
//         int mil = (taille/2);
//         return tab[mil];
//     }
// }


// void jugementMajoritaire(ListCand* lstCand,ListElect* lstElect,char* fichier){
//     initJugement(lstCand,lstElect,fichier);
//     trierVotes(lstCand,lstElect->size);
//     Candidat* gagnant = lstCand->head;
//     int taille = lstElect->size;
//     double verifMed = mediane(gagnant->jugement,taille);
//     double verifMoy = moyenne(gagnant->jugement,taille);
    
//     //comparer tous les candidats et leur médiane et prendre celui qui a le plus haut. Si il y a égalité entre 2 candidats, comparer la moyenne des candidats égaux
//     for(Candidat* c = lstCand->head->next;c!=NULL;c=c->next){
//         int valEtudiee = mediane(c->jugement,taille);
//         if(valEtudiee<verifMed){
//             verifMed=valEtudiee;
//             gagnant = c;
//         }
//         else if(valEtudiee == verifMed){
//             int moyenneEtudiee = moyenne(c->jugement,taille);
//             if(moyenneEtudiee<verifMoy){
//                 gagnant = c;
//                 verifMoy=moyenneEtudiee;
//             }
//         }
//     }
//     printf("Le gagnant est : %s\n",gagnant->prenom);

// }




// int main(int argc,char** argv){
//     char* fichier = "../Data/vote10.csv";
//     ListCand* lstCand = listCand_create();
//     ListElect* lstElect = listElect_create();
    
    
//     getCandidat(lstCand,fichier);
//     int tab[lstCand->size];
//     lstElect = getElecteur(lstElect,lstCand,fichier,tab);
//     printf("taille:%d\n",lstElect->size);

//     // initJugement(lstCand,lstElect,fichier);

    
//     // trierVotes(lstCand,lstElect->size);
//     // for(Candidat* c = lstCand->head;c!=NULL;c = c->next){
//     //     printf("\nCandidat : %s :\n",c->prenom);
//     //     for(int i = 0;i<lstElect->size;i++){
//     //         printf("vote : %d ",c->jugement[i]);
//     //     }
//     // }

//     //Candidat* top = lstCand->head;

//     printf("\n\n*******************\n\n");
//     jugementMajoritaire(lstCand,lstElect,fichier);

//     printf("\n\n");
//     tableauDelete(lstCand);
//     listCand_delete(lstCand);
//     listElect_delete(lstElect);
//     printf("delete fini\n");

//     return 0;
// }