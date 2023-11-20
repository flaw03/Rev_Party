#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>


#include "Uninominales.h"


int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Erreur USAGE[%s], veuillez insérer un fichier.csv puis choisir 'un' ou 'deux'\n", argv[0]);
        exit(1);
    }


    // FILE* logfile; //RENDRE FONCTIONNEL DèS QU'ON A LE GETOPT.H

    // if (getoppt contient -o) {
    //     logfile = fopen("log.txt", "w");
    //     if (logfile == NULL) {
    //         printf("erreur fichier.\n");
    //         return 1;
    //     }
    // } else {
    //     logfile = stdout;
    // }

    //  if (logfile != stdout) {
    //     fclose(logfile);
    // }
    
    FILE* logfile = fopen("log.txt", "w");

    if (strcmp(argv[2], "un") == 0) {
        unTour(argv[1], logfile);
    }
    else if (strcmp(argv[2], "deux") == 0) {
        deuxTours(logfile, argv[1]);
    }  
    else {
        fprintf(stderr, "Erreur USAGE[%s] Veuillez choisir 'un' ou 'deux'\n", argv[2]);
        fclose(logfile);
        exit(2);
    }
    fclose(logfile);

    return 0;
}
