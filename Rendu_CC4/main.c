#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <getopt.h>

#include "inc/Utiles.h"
#include "inc/lecture_csv.h"
#include "inc/uninominales.h"
#include "inc/utils_tab.h"
#include "inc/condorcet.h"
#include "inc/jugement.h"

/**
 *	@defgroup Main Test program for Uninominales Implantation
 *  @brief Definition of the Uninominales type and operators
 *  @{
 */


/** Print a usage message for this program.
 
 @code{.unparsed}
 $bin/uninominales -i <filename.csv> | -d <nomFichierCSV> [-o <log_file>] -m {uni1, uni2, all, cm, cp, cs)}

Options :
  -i <filename.csv> > : Traite le fichier CSV spécifié.
  -d <filename.csv> > : Traite le fichier CSV spécifié.
  -o <<filename.csv> >    : Spécifie le fichier de log (optionnel).
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
    bool optvalide = false;
    char* methode = NULL;
    Matrice matriceDuel = NULL;
    FILE* logfile = stdout;
    int nbrElecteur;

    
    if(argc<5){
            fprintf(stderr, "Usage: %s -i <filename.csv> | -d <filename.csv> -m {uni1, uni2, cm, cp, cs,jm, all} [-o <log_file>]\n", argv[0]);
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
                fprintf(stderr, "Usage: %s -i <filename.csv>  | -d <filename.csv> -m {uni1, uni2, cm, cp, cs,jm, all} [-o <log_file>]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    if ((optionBalot && optionMatrice) || (!optionMatrice && !optionBalot) ) {
        fprintf(stderr, "Erreur : Les options -i et -d ne peuvent pas être présentes simultanément.\n");
        exit(EXIT_FAILURE);
    }
    if (methode == NULL){
        fprintf(stderr, "Usage: %s -i <filename.csv>  | -d <filename.csv> -m {uni1, uni2, cm, cp, cs,jm, all} [-o <log_file>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if (strcmp(methode,"all") == 0){
        optionAll = true;
        optvalide = true;
    }

    if((strcmp(methode,"uni1") == 0  || optionAll ) && optionBalot){
        unTour(filename,logfile);    
        optvalide = true;
        
    }
    if((strcmp(methode,"uni2" ) == 0   || optionAll) && optionBalot){
        deuxTours(logfile,filename);
        optvalide = true;
    }
    if(strcmp(methode,"cm") == 0 || optionAll ){
        int vainqueur = methode_Minimax(matriceDuel,logfile);
        char * nomVainqueur = obtenir_nom_Candidat(filename,vainqueur,optionBalot);
        printf("Mode de Scrutin : Condorcet Minimax, %d candidats, %d votants, vainqueur = %s\n",matriceDuel->nb_colonne,
        nbrElecteur,nomVainqueur);
        free(nomVainqueur);
        optvalide = true;

    }

    if(strcmp(methode,"cp") == 0 || optionAll ){
        int vainqueur = methode_Rangement_Des_Paires(matriceDuel,logfile);
        char * nomVainqueur = obtenir_nom_Candidat(filename,vainqueur,optionBalot);
        printf("Mode de Scrutin : Condorcet paires, %d candidats, %d votants, vainqueur = %s\n",matriceDuel->nb_colonne,
        nbrElecteur,nomVainqueur);
        free(nomVainqueur);
        optvalide = true;

    }

    if(strcmp(methode,"cs") == 0 || optionAll){
        int vainqueur = methode_Schulze(matriceDuel,logfile);
        char * nomVainqueur = obtenir_nom_Candidat(filename,vainqueur,optionBalot);
        printf("Mode de Scrutin : Condorcet Shulze, %d candidats, %d votants, vainqueur = %s\n",matriceDuel->nb_colonne,
        nbrElecteur,nomVainqueur);
        free(nomVainqueur);
        optvalide = true;

    }

    if((strcmp(methode,"jm") == 0 || optionAll) && optionBalot){
        voteJugementMajoritaireBallot(filename,logfile);
        optvalide = true;
    }
    
    if (!optvalide){
        fprintf(stderr, "Usage: %s -i <filename.csv>  | -d <filename.csv> -m {uni1, uni2, cm, cp, cs,jm, all} [-o <log_file>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    


    if(logfile!=stdout){
        fclose(logfile);
    }
    delete_Matrice(matriceDuel);
    exit(0);
}