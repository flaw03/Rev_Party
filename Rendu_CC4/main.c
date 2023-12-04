#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <getopt.h>

#include "../Rendu_CC4/fichiers.h/Utiles.h"
#include "../Rendu_CC4/fichiers.h/lecture_csv.h"
#include "../Rendu_CC4/fichiers.h/Uninominales.h"
#include "../Rendu_CC4/fichiers.h/utils_tab.h"
#include "../Rendu_CC4/fichiers.h/condorcet.h"
#include "../Rendu_CC4/fichiers.h/jugement.h"

/**
 *	@defgroup Main Test program for Uninominales Implantation
 *  @brief Definition of the Uninominales type and operators
 *  @{
 */


/** Print a usage message for this program.
 
 @code{.unparsed}
 $bin/uninominales -i <filename.csv> | -d <nomFichierCSV> [-o <log_file>] -m {uni1, uni2, all, cm, cp, cs)}

Options :
  -i <nomFichierCSV> : Traite le fichier CSV spécifié.
  -d <nomFichierCSV> : Traite le fichier CSV spécifié.
  -o <fichierLog>    : Spécifie le fichier de log (optionnel).
  -m <methode>        : Précise la méthode de scrutin à utiliser.

Notez que la commande doit contenir soit -i ou -d, mais pas les deux en même temps.
 
 @endcode
 */

//Compile with : make



int main(int argc, char** argv) {
    int opt;
    char* filename = NULL;
    char* fichierLog = NULL;
    bool optionBalot = false;
    bool optionAll = false;
    bool optionMatrice = false;
    char* methode = NULL;
    Matrice matriceDuel = NULL;
    FILE* logfile = stdout;
    int nbrElecteur;

    
    if(argc<5){
            fprintf(stderr, "Usage: %s -i ../Data/nomFichierCSV> | -d ../Data/<nomFichierCSV>  -m {uni1, uni2, cm, cp, cs,jm, all} [-o <log_file>]\n", argv[0]);
            exit(9);
        }
    while ((opt = getopt(argc, argv, "i:o:m:d:")) != -1) {
        switch (opt) {
            case 'i':
                filename= optarg;
                nbrElecteur = lireBallot(filename,&matriceDuel);
                optionBalot = true;
                break;
            case 'd':
                filename = optarg;
                nbrElecteur = lireMatriceDuel(filename,&matriceDuel);
                optionMatrice = true;
                break;
            case 'o':                       
                fichierLog = optarg;
                logfile = fopen(fichierLog, "w");
                if (logfile == NULL) {
                    printf("erreur fichier.\n");
                    exit(33);
                }
                break;
            case 'm':
                methode = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s -i ../Data/<nomFichierCSV> | -d ../Data/<nomFichierCSV>  -m {uni1, uni2, cm, cp, cs,jm, all} [-o <log_file>]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    if ((optionBalot && optionMatrice) || (!optionMatrice && !optionBalot) ) {
        fprintf(stderr, "Erreur : Les options -i et -d ne peuvent pas être présentes simultanément.\n");
        exit(EXIT_FAILURE);
    }
    if (methode == NULL){
        fprintf(stderr, "Erreur : Les options -i et -d ne peuvent pas être présentes simultanément.\n");
        exit(EXIT_FAILURE);
    }
    if (strcmp(methode,"all") == 0){
        optionAll = true;
    }

    if((strcmp(methode,"uni1") == 0  || optionAll ) && optionBalot){
         unTour(filename,logfile);    
    }
    if((strcmp(methode,"uni2" )==0   || optionAll) && optionBalot){
        deuxTours(logfile,filename);
    }
    if(strcmp(methode,"cm")==0 || optionAll ){
        int vainqueur = methode_Minimax(matriceDuel,logfile);
        char * nomVainqueur = obtenir_nom_Candidat(filename,vainqueur,optionBalot);
        printf("Mode de paire : Condorcet Minimax, %d candidats, %d votants, vainqueur = %s\n",matriceDuel->nb_colonne,
        nbrElecteur,nomVainqueur);
        free(nomVainqueur);
    }
    if(strcmp(methode,"cp") ==0 || optionAll ){
        int vainqueur = methode_Rangement_Des_Paires(matriceDuel,logfile);
        char * nomVainqueur = obtenir_nom_Candidat(filename,vainqueur,optionBalot);
        printf("Mode de paire : Condorcet paires, %d candidats, %d votants, vainqueur = %s\n",matriceDuel->nb_colonne,
        nbrElecteur,nomVainqueur);
        free(nomVainqueur);
    }
    if(strcmp(methode,"cs") ==0 || optionAll){
        int vainqueur = methode_Schulze(matriceDuel,logfile);
        char * nomVainqueur = obtenir_nom_Candidat(filename,vainqueur,optionBalot);
        printf("Mode de paire : Condorcet Shulze, %d candidats, %d votants, vainqueur = %s\n",matriceDuel->nb_colonne,
        nbrElecteur,nomVainqueur);
        free(nomVainqueur);
    }
     if((strcmp(methode,"jm") == 0 || optionAll) && optionBalot){
        voteJugementMajoritaireBallot(filename,logfile);
    }
    else{
        fprintf(stderr,"Usage [%s] use -m {uni1, uni2, cm, cp, cs,jm, all}\n",argv[0]);
    }
    


    if(logfile!=stdout){
        fclose(logfile);
    }
    delete_Matrice(matriceDuel);
    exit(0);
}
