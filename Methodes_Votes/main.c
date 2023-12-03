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
#include "jugement.h"

//Compiler avec : make



int main(int argc, char** argv) {
    int opt;
    char* fichierCsv=NULL;
    char* fichierLog=NULL;
    bool hasLog = false;
    char* methode = NULL;
    FILE* logfile = NULL;
    
        if(argc<5){
        
            fprintf(stderr,"Erreur,Usage[%s], nombre d'arguments invalides , veuillez effectuer :\n./bin/main -i ../Data/<fichier.csv> -o <fichier log> -m {uni1,uni2,all,jm}  \nou\n./bin/main -i ../Data/<fichier.csv> -m {uni1,uni2,all,jm}\n",argv[0]);
            exit(9);
        }
    while ((opt = getopt(argc, argv, "i:o:m:")) != -1) {
        switch (opt) {
            case 'i':
                fichierCsv= optarg;
                printf("%s\n",fichierCsv);
               
                break;
            case 'o':                       
                fichierLog = optarg;
                hasLog = true;
                break;
            case 'm':
                methode = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s -i inputfile -o outputfile -m mode\n", argv[0]);
                exit(EXIT_FAILURE);
        }
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

    if(strcmp(methode,"uni1")==0){
        unTour(fichierCsv,logfile);
    }
    else if(strcmp(methode,"uni2")==0){
        deuxTours(logfile,fichierCsv);
    }
    else if(strcmp(methode,"all")==0){
        unTour(fichierCsv,logfile);
        deuxTours(logfile,fichierCsv);
        voteJugementMajoritaireBallot(fichierCsv,logfile);
    }
    else if(strcmp(methode,"jm")==0){
        voteJugementMajoritaireBallot(fichierCsv,logfile);
    }

    if(logfile!=stdout){
        fclose(logfile);
    }





    

    return 0;
}
