#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <getopt.h>

// #include "Utiles.h"
#include "lecture_csv.h"
// #include "Uninominales.h"
#include "utils_tab.h"
#include "logfp.h"
#include "condorcet.h"

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
    bool optionBalot = false;
    bool optionAll = false;
    bool optionMatrice = false;
    char* methode = NULL;
    Matrice matriceDuel = NULL;
    int nbrElecteur;

    
    if(argc<5){
            fprintf(stderr, "Usage: %s -i <nomFichierCSV> | -d <nomFichier>  -m {uni1, uni2, cm, cp, cs, all} [-o <log_file>]\n", argv[0]);
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
                hasLog = true;
                ouvrirLog(fichierLog);
                break;
            case 'm':
                methode = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s -i <nomFichierCSV> | -d <nomFichier>  -m {uni1, uni2, cm, cp, cs, all} [-o <log_file>]\n", argv[0]);
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
    if (trcmp(methode,"all") == 0){
        optionAll = true;
    }

    // if((strcmp(methode,"uni1") == 0  || optionAll ) && optionBalot){
         // unTour(filename,logfile);    
    // }
    // else if((strcmp(methode,"uni2" )==0   || optionAll) && optionBalot){
    //     // deuxTours(logfile,filename);
    // }
    // else
    if(strcmp(methode,"cm")==0 || optionAll ){
        int vainqueur = methode_Minimax(matriceDuel);
        char * nomVainqueur = obtenirNomCandidat(filename,vainqueur);
        printf("Mode de paire : Condorcet paires, %d candidats, %d votants, vainqueur = %s\n",matriceDuel->nb_colonne,
        nbrElecteur,nomVainqueur);
        free(nomVainqueur);
    }
    else if(strcmp(methode,"cp")==0 || optionAll ){
        int vainqueur = methode_Rangement_Des_Paires(matriceDuel);
        char * nomVainqueur = obtenirNomCandidat(filename,vainqueur);
        printf("Mode de paire : Condorcet paires, %d candidats, %d votants, vainqueur = %s\n",matriceDuel->nb_colonne,
        nbrElecteur,nomVainqueur);
        free(nomVainqueur);
    }
    else if(strcmp(methode,"cs")==0 || optionAll){
        int vainqueur = methode_Schulze(matriceDuel);
        char * nomVainqueur = obtenirNomCandidat(filename,vainqueur);
        printf("Mode de paire : Condorcet Shulze, %d candidats, %d votants, vainqueur = %s\n",matriceDuel->nb_colonne,
        nbrElecteur,nomVainqueur);
        free(nomVainqueur);
    }
    else{
        fprintf(stderr, "Usage: %s-i <nomFichierCSV> | -d <nomFichier>  -m {uni1, uni2, cm, cp, cs, all} [-o <log_file>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if (hasLog){
        closeLog();
    }
    delete_Matrice(matriceDuel);
    exit(0);
}
