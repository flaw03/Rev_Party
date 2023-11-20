#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

#include "logfp.h"

int fichierLog;

void ouvrirLog(const char* nom_fichier){
    fichierLog = open(nom_fichier,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
    if(fichierLog==-1){
        perror("echec ouverture fichier log");
        exit(1);
    }

    int duppliquer= dup2(fichierLog,1);
     if (duppliquer==-1){
      perror("echec de la duplication");
      exit(1);
    }
}



void closeLog(void){
    close(fichierLog);
}

