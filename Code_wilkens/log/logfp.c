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
 fichierLog= open(nom_fichier,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
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

void closeLog(int desc){
    close(desc);
}

int main() {
    //test de la fonction
    //main parametre pour obtenir balise -o pour voir s'il y a un fichier avant de faire dup pas tester ici dans le programme final
    ouvrirLog("log.txt");

    printf("debut\n");
    char aux[512];

    for(int i=0;i<10;i++){
        sprintf(aux,"%d",i);
        
        printf("i= %s\n",aux);
    }

    printf("Fin du programme");
    close(fichierLog);
    return 0;
}
