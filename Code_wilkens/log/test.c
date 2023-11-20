
#include <stdlib.h>
#include <stdio.h>

#include "logfp.h"


int main(void) {
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
    closeLog();
    return 0;
}
