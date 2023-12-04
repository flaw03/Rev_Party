#include <fcntl.h>
#include <unistd.h>
#include "logfp.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int fichierLog;

void ouvrirLog(const char* nom_fichier) {
    fichierLog = open(nom_fichier, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fichierLog == -1) {
        perror("Échec de l'ouverture du fichier log");
        exit(EXIT_FAILURE);
    }

}


void closeLog(void){
    close(fichierLog);
}

