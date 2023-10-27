#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sha256/sha256.h"
#include "Sha256/sha256_utils.h"
#include <ctype.h>
#define STRLONG 60
// SMETS YoannFrFua2beaG
// NDOYE AssaneZdINR7yriJJ
char* miseenforme();
int indice_sha();
char* nomFichier();
void extractCSVRowValues();
#define MAX_LINE_LENGTH 1024

int main(int argc ,char** argv){
	if(argc!=2){
		fprintf(stderr,"Veillez à seulement à lancer le programme , je m'occupe de tout ;)\n");
		exit(18);
	}
	char* fichier = (char*)malloc(40);
	fichier = nomFichier();
	char * nom = (char *)malloc(40);
	char * prenom = (char *)malloc(40);
	char * cle = (char *)malloc(40);
	int bufferSize = SHA256_BLOCK_SIZE;
	char hashRes[bufferSize*2 + 1]; // contiendra le hash en hexadécimal
	char * item = malloc(STRLONG*sizeof(char)); // contiendra la chaîne à hasher
	printf("Entrez votre nom : ");
	scanf("%s",nom);
	printf("Entrez votre prénom  : ");
	scanf("%s",prenom);
	printf("Entrez votre cle secrète : ");
	scanf("%s",cle);
	item = miseenforme(nom,prenom,cle,item);
	sha256ofString((BYTE *)item,hashRes); // hashRes contient maintenant le hash de l'item
	int long_hash = strlen(hashRes); // sa longueur en caractères hexadécimaux
	printf("La combinaison (%s) a donné le sha :\n - %s\n",item,hashRes);
	int index = indice_sha(hashRes,fichier);
	char* values = (char *)malloc(1024);
	char line[MAX_LINE_LENGTH];
	extractCSVRowValues(fichier,index);
	
free(nom);
free(prenom);
free(cle);
free(item);

return 0;
}

char* miseenforme(char* nom,char* prenom,char* cle,char* item){
	for(int i = 0;nom[i]!='\0';i++){
		nom[i] = toupper(nom[i]);
	}
	for(int i = 0;prenom[i]!='\0';i++){
		prenom[i] = tolower(prenom[i]);

	}
	prenom[0] = toupper(prenom[0]);

	strcat (prenom,cle);
	strcat (item,nom);
	strcat(item," ");
	strcat(item,prenom);
	return item;


}

char* nomFichier(){

	int i;
	printf("Voulez-vous ouvrir le fichier jugement.csv (1) ou VoteCondorcet.csv (2) ?\n Veuillez rentrer votre réponse 1 ou 2 : ");
	scanf("%d",&i);
	if(i == 1){
		return "jugement.csv";
	}
	if(i==2){
		return "VoteCondorcet.csv";
	}
	else{
		printf("AH ! mauvais fichier mon boeuf\n");
		exit(45);
	}
}

int indice_sha(char* chaine,char* fichier){
    FILE* file = fopen(fichier,"r");
    if (file == NULL) {
        perror("Impossible d'ouvrir le fichier\n");
        exit(28);
    }
    char line[MAX_LINE_LENGTH];
    int colonne = 3;
    int isFirstLine = 1; // esquive la première ligne
	int indice =2;
    // Lire chaque ligne du fichier CSV
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        // Ignorer la première ligne
        if (isFirstLine) {
            isFirstLine = 0;
            continue;
        }

        char* token = strtok(line, ",");
        int colonneActuelle = 0;

        // Parcourir les tokens (colonnes)
        while (token != NULL) {
            // Si nous avons atteint la colonne souhaitée, l'afficher
            if (colonneActuelle == colonne) {
				if(strcmp(chaine,token) == 0){
					fclose(file);
					return indice;
				}
				indice++;   
            }
            // Obtenir le prochain token
            token = strtok(NULL, ",");
            colonneActuelle++;
        }
    }
	return -1;
    printf("\n");
    fclose(file);
}

void extractCSVRowValues(const char *filename, int lineNumber) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    char line[1024];
    int currentLine = 0;

    while (fgets(line, sizeof(line), file)) {
        currentLine++;
        
        if (currentLine == lineNumber) {
            char *token = strtok(line, ",");
            int columnNumber = 1;
			int cpt = 1;
            while (token != NULL) {
                if (columnNumber >4) {
                    printf("Vote %d : %s\n", cpt, token);
					cpt++;
                }
                token = strtok(NULL, ",");
                columnNumber++;
            }
            return; // Sortir de la boucle après avoir trouvé la ligne souhaitée
        }
    }

    fclose(file);
}
