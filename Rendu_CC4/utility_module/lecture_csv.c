#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "lecture_csv.h"
#include "utils_tab.h"
#include "utiles.h"

#define MAX_LIGNES 1024
#define MAX_COLONNES 1024
#define MAX_LINE_LENGTH 1024
#define MARGE 4
#define COLONNE_SHA 3
#define BUFFER_SIZE 16
#define colonneID 0
#define SIZE_TAB 50




/*
*    Equipe 17 : NDOYE Assane, SMETS Yoann, JOSEPH Wilkens Marc Johnley, MORELLATO Adrian
*/


/*
*   Fonction pour tester que le fichier en paramètre est bien un csv
*/


int fichierValide(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s.\n", filename);
        exit(1); // Code d'erreur pour une ouverture de fichier échouée
    }

    char line[1024]; // Taille maximale d'une ligne

    // Ignorer la première ligne
    if (fgets(line, sizeof(line), file) == NULL) {
        fprintf(stderr, "Erreur : Fichier vide.\n");
        fclose(file);
        return -2; // Code d'erreur pour un fichier vide
    }

    // Lire le reste des lignes
    while (fgets(line, sizeof(line), file) != NULL) {
        
        // Ignorer les lignes vides
        if (strlen(line) <= 1) {
            continue;
        }

        // Trouver la quatrième colonne (indice 3) en utilisant des tabulations comme séparateurs
        char *token = strtok(line, "\t");
        int col = 0;
        while (token != NULL) {
            if (col == 3) {
                // Vérifier si la valeur n'est pas un entier
                if (isInteger(token)) {
                    fclose(file);
                    return 1; // Code d'erreur pour une valeur entière trouvée
                }
            }
            else if(col == 6){
                if (!isInteger(token)){
                    fclose(file);
                    return 1;
                }
            }
            col++;
            token = strtok(NULL, "\t");
        }
    }

    fclose(file);
    return 0; // Aucune erreur détectée
}

void isCSV(const char* filename) {
    const char* extension = strrchr(filename, '.');
    if (extension != NULL) {
        if (strcmp(extension, ".csv") == 0) {
            return ;
        }
    }
    fprintf(stderr, "ERREUR : Le fichier '%s' n'est pas au bon format. L'extension attendue est '.csv'.\n", filename);
    exit(33);
}

/*
*    Fonction qui renvoie le nom d'un candidat
*/
char * formatage_nomCandidat(char * nom){
        if (nom != NULL) {
        // Allouer de la mémoire pour la chaîne et la copier
        size_t len = strcspn(nom, "\n");
        if (len > 0 && nom[len - 1] == '\r') {
            // Pour les fichiers texte Windows, enlever également le caractère de retour de chariot (\r)
            len--;
        }

        // Allouer de la mémoire pour la chaîne et la copier
        char *result = (char *)malloc(len + 1);
        if (result == NULL) {
            perror("Erreur lors de l'allocation de mémoire");
            exit(28);
        }

        strncpy(result, nom, len);
        result[len] = '\0';  // Ajouter le caractère de fin de chaîne
        return result;
    } else {
        // Allouer de la mémoire pour la chaîne et la copier
        char *result = (char *)malloc(strlen("Candidat Introuvable") + 1);
        if (result == NULL) {
            perror("Erreur lors de l'allocation de mémoire");
            exit(28);
        }
        strcpy(result, "Candidat Introuvable");
        return result;
    }
}

char * obtenir_nom_Candidat_matrice(const char *filename,int numColonne){
    isCSV(filename);
    FILE *file = fopen(filename, "r");
     if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(28);
    }
    char line[MAX_LINE_LENGTH];

    if (fgets(line, MAX_LINE_LENGTH, file) == NULL){
        perror("fegts");
        exit(1);
    };
    fclose(file);
    const char *delimiteur = ",";
    char* token = strtok(line,delimiteur);
    int nb_candidat = 0;
    while (token != NULL && nb_candidat < numColonne){
        token = strtok(NULL,delimiteur);
        nb_candidat ++;
    }
    return formatage_nomCandidat(token);
}


char * obtenir_nom_Candidat_ballot(const char *filename,int numColonne){
    isCSV(filename);
    FILE *file = fopen(filename, "r");
     if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(28);
    }
    char line[MAX_LINE_LENGTH];
    // lit la premier ligne 
    if (fgets(line, MAX_LINE_LENGTH, file) == NULL){
        perror("fegts");
        exit(1);
    };
    fclose(file);
    char* token = strtok(line, ",");
    for (int  i = 0 ; i < MARGE + numColonne; i++){
        token = strtok(NULL, ",");
    }
    return formatage_nomCandidat(token);
}

char * obtenir_nom_Candidat(const char *filename,int numColonne,bool isBallot){
    if (isBallot){
        return obtenir_nom_Candidat_ballot(filename,numColonne);
    }else{
        return obtenir_nom_Candidat_matrice(filename,numColonne);
    }
}

/*
*    Fonction qui renvoie une ligne d'un hash doné
*/
void afficher_vote(const char* filename,char* hash){
    isCSV(filename);
    FILE* file = fopen(filename,"r"); 
    if (file == NULL) {
        perror("Impossible d'ouvrir le fichier\n");
        exit(28);
    }
    char line[MAX_LINE_LENGTH];
    char *tabCandidat[SIZE_TAB];
    int nbCandidat = 0;
    bool find = false ;
    if (fgets(line, MAX_LINE_LENGTH, file) == NULL){
        perror("fegts");
        exit(1);
    };
    char*  token = strtok(line, ",");
    for(int i = 0;i<MARGE;i++){
        token = strtok(NULL,",");//Récupère le nom des candidats
    }

    for (int i = 0; token != NULL; i++){
        tabCandidat[i] = formatage_nomCandidat(token);
        token = strtok(NULL, ",");
        nbCandidat ++;
    }
    // Lire chaque ligne du fichier CSV
    while (fgets(line, MAX_LINE_LENGTH, file) && !find) {
        token = strtok(line, ",");
        for(int i = 0;i<MARGE-1;i++){//Se place dans la colonne des votes
            token = strtok(NULL,",");
        }
        if(strcmp(token,hash) == 0){// HASH trouvé 
            token = strtok(NULL, ",");   
            printf("Candidat |Vote\n");                 
            for (int i = 0 ; i < nbCandidat && token != NULL ; i++) {
                printf("%-30s|%s\n",tabCandidat[i],token);
                token = strtok(NULL, ",");   
            }
            find = true;
        }
    }
    for (int i = 0; i < nbCandidat ; i++){
        free(tabCandidat[i]);
    }
    if (!find){
        printf("Électeur non trouvé dans la liste,veillez à bien orthographier votre nom,prénom,clé\n");
    }
    fclose(file);
}



int lireBallot(char* filename,Matrice *matrice){
    isCSV(filename);
    FILE *file = fopen(filename, "r");
     if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(28);
    }
    char line[MAX_LINE_LENGTH];

    // lit la premier ligne 
     if (fgets(line, MAX_LINE_LENGTH, file) == NULL){
        perror("fegts");
        exit(1);
    };
    char* token = strtok(line, ",");
    int nb_candidat = 0;
    while (token != NULL){
        token = strtok(NULL, ",");
        nb_candidat ++;
    }
    nb_candidat -= MARGE;
    int nombreVotant = 0;
    
    *matrice = create_Matrice(nb_candidat,nb_candidat);
    init_Matrice(*matrice,0);
    
    Tableau tableauVote = create_Tableau(nb_candidat);
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char* token = strtok(line, ",");
        int colonne = 0;
        nombreVotant++;
        while (token != NULL) {
            if (colonne > MARGE - 1 ) { //Colonne 3 = colonne des SHA 
                tableauVote->tableau[colonne - MARGE] = atoi(token);
            }
            token = strtok(NULL, ",");
            colonne++;
        }
        remplire_Matrice_Duel(*matrice,tableauVote);
    }
    delete_Tableau(tableauVote);
    fclose(file);
    return nombreVotant;
}



int lireMatriceDuel(char* filename,Matrice *matrice){
    isCSV(filename);
    FILE *file = fopen(filename, "r");
     if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(28);
    }
    char line[MAX_LINE_LENGTH];

    // lit la premier ligne 
     if (fgets(line, MAX_LINE_LENGTH, file) == NULL){
        perror("fegts");
        exit(1);
    };
    const char *delimiteur = ",";
    char* token = strtok(line,delimiteur);
    int nb_candidat = 0;
    while (token != NULL){
        token = strtok(NULL,delimiteur);
        nb_candidat ++;
    }
    
    *matrice = create_Matrice(nb_candidat,nb_candidat);
    init_Matrice(*matrice,0);
    
    for (int i = 0; i < (*matrice)->nb_ligne;i++){
        if (fgets(line, MAX_LINE_LENGTH, file) == NULL){
            perror("fgets");
            exit(3);
        }
        token = strtok(line, delimiteur);
        for (int j = 0 ;j < (*matrice)->nb_colonne && token != NULL;j++){
            (*matrice)->tableau[i][j] = atoi(token);
            token = strtok(NULL, delimiteur);
        }
    }
    fclose(file);
    return (*matrice)->tableau[0][1] + (*matrice)->tableau[1][0];
}

void removeNewline(char* str) {
    size_t length = strlen(str);

    for (size_t i = 0; i < length; ++i) {
        if (str[i] == '\r' || str[i] == '\n') {
            str[i] = '\0';
        }
    }
}




ListElect* getElecteur(ListElect* lstElect,ListCand* lstCand,char* fichier,int* tab) {
   if(fichierValide(fichier)==1){
        fprintf(stderr,"Fichier transmis non valide,veuillez vérifier la conformité des données\n");
        exit(2);
    }
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
            else if (colonneActuelle == COLONNE_SHA) {// Association NOM au prenom
                prenom = strdup(token);
                removeNewline(prenom);
            }
            else if (colonneActuelle >= MARGE) { // Récupération de chaque vote , si vote non comptabilisé => pire valeur
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
    if(lstElect == NULL){
    	fprintf(stderr,"Fichier.csv invalide");
    	exit(1);
    }
    return lstElect;
    
}

ListCand* getCandidat(ListCand* lstCand,char* fichier){
    if(fichierValide(fichier)==1){
        fprintf(stderr,"Fichier transmis non valide,veuillez vérifier la conformité des données\n");
        exit(2);
    }

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
            if (colonneActuelle >= MARGE) {
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
        if(lstCand == NULL){
    	fprintf(stderr,"Fichier.csv invalide");
    	exit(20);
    }
        return lstCand;
    }
    }
    fclose(file);
    if(lstCand == NULL){
    	fprintf(stderr,"Fichier.csv invalide");
    	exit(20);
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
                if (colonneActuelle >= MARGE) {
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
            else if (colonneActuelle == COLONNE_SHA) {
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
           if(colonneActuelle>=MARGE){
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

void verifFichier(const char* filename){
    if(fichierValide(filename)==1){
    fprintf(stderr,"Fichier non valide, non respect des normes de remplissage du fichier,les votes doivent commencer à partir de la colonne 4.\n");
    exit(EXIT_FAILURE);
    }
}


