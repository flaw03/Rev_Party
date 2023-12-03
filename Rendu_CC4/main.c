#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <getopt.h>

#include "Utiles.h"
#include "lecture.h"
#include "Uninominales.h"
#include "utils_tab.h"

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
    bool hasLog = false;
    bool optionBalot = NULL;
    char* methode = NULL;
    FILE* logfile = NULL;
    Matrice matriceDuel = NULL;
    int nbrElecteur;

    
    if(argc<5){
            fprintf(stderr, "Usage: %s-i <nomFichierCSV> | -d <nomFichier>  -m {uni1, uni2, all} [-o <log_file>]\n", argv[0]);
            exit(9);
        }
    while ((opt = getopt(argc, argv, "i:o:m:")) != -1) {
        switch (opt) {
            case 'i':
                filename= optarg;
                nbrElecteur = lireBallot(filename,&matriceDuel);
                optionBalot = true;
                break;
            case 'd':
                filename = optarg;
                nbrElecteur = lireMatriceDuel(filename,&matriceDuel);
                optionBalot = false;
                break;
            case 'o':                       
                fichierLog = optarg;
                hasLog = true;
                break;
            case 'm':
                methode = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s-i <nomFichierCSV> | -d <nomFichier>  -m {uni1, uni2, all} [-o <log_file>]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    if (optionBalot && (optind < argc) && (argv[optind][0] == '-' && argv[optind][1] == 'd')) {
    fprintf(stderr, "Erreur : Les options -i et -d ne peuvent pas être présentes simultanément.\n");
    exit(EXIT_FAILURE);
    }

    if(hasLog) {
        logfile = fopen(fichierLog, "w");
        if (logfile == NULL) {
            printf("erreur fichier.\n");
            return 1;
        }
    } else if(!hasLog) {
        logfile = stdout;
    }

    if(strcmp(methode,"uni1") == 0 && optionBalot ){
        unTour(filename,logfile);
    }
    else if(strcmp(methode,"uni2")==0 && optionBalot){
        deuxTours(logfile,filename);
    }
    else if(strcmp(methode,"cm")==0){
        int vainqueur = methode_Minimax(matriceDuel);
    }
    else if(strcmp(methode,"cp")==0){
        int vainqueur = methode_Rangement_Des_Paires(matriceDuel);
        char * nomVainqueur = obtenir_nom_Candidat(filename,vainqueur);
        printf("Mode de paire : Condorcet paires, %d candidats, %d votants, vainqueur = %s\n",matriceDuel->nb_colonne,
        nbrElecteur,nomVainqueur);
        free(nomVainqueur);
    }
    else if(strcmp(methode,"cs")==0){
        int vainqueur = methode_Schulze(matriceDuel);
        char * nomVainqueur = obtenir_nom_Candidat(filename,vainqueur);
        printf("Mode de paire : Condorcet Shulze, %d candidats, %d votants, vainqueur = %s\n",matriceDuel->nb_colonne,
        nbrElecteur,nomVainqueur);
        free(nomVainqueur);
    }
    else if(strcmp(methode,"all")==0){
        unTour(filename,logfile);
        deuxTours(logfile,filename);
    }

    if(logfile!=stdout){
        fclose(logfile);
    }
    if (matriceDuel != NULL){
        delete_Matrice(matriceDuel);
    }


    return 0;
}
