#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <ctype.h>

#include "../utility_module/lecture_csv.h"
#include "../sha256_module/sha256.h"
#include "../sha256_module/sha256_utils.h"
#define STRLONG 100



/*
*     On compile avec la commande make verify_my_vote
*     Et on lance le programme avec bin/verify_my_vote nom_fichier.csv
*/

/*
*    Cette fonction permet de mettre sous la bonne forme le ou les prénoms du votant 
*    (La première lettre du/des prénom(s) en majuscule et les autres en minuscule)
*    En effet, on a pu constater que pour Wilkens, il était plus compliqué d'avoir le bon format, d'où l'existence de cette fonction
*    Une fonction comme celle ci est inutile, étant donné que le nom doit être entièrement en majuscules
*/

void conversionPrenom(char* prenom) {
	// Mise en majuscule de la première lettre
	prenom[0] = toupper(prenom[0]);
	for (int i = 1; i < (int)strlen(prenom); i++) {
		if (prenom[i] == ' ') {
			// Mise en majuscule de la première lettre de chaque nouveau prénom
			i++;
			prenom[i] = toupper(prenom[i]);
		}
		else
		{
			// Mise en minuscule des autres lettres
			prenom[i] = tolower(prenom[i]);
		}
	}
}

/*
*    Fonction qui concatène nom, prénom et clé et en fait un sha256
*/
void concatAndHash(char* nom, char* prenom, char* cle, char* hashRes) {
	char* item = malloc(STRLONG * sizeof(char));
	strcpy(item,nom);
	strcat(item," ");
	strcat(item,prenom);
	strcat(item,cle);
	sha256ofString((BYTE*)item, hashRes);
	free(item);
}


/*
*    Fonction main
*/
int main(int argc, char** argv) {

	if (argc != 2) {
		fprintf(stderr, "Usage : %s fillname\n",argv[0]);
		exit (1);
	}
	
	const char* filename = argv[1];
	
	char nom[100];
	printf("Entrez votre nom : ");
	fgets(nom, sizeof(nom), stdin);

	// Supprimer le caractère de nouvelle ligne du dernier nom saisi
	nom[strcspn(nom, "\n")] = 0;

	// Convertir en majuscules
	for (int i = 0; nom[i] != '\0'; i++)
		nom[i] = toupper(nom[i]);

	char prenom[100];
	printf("Entrez votre prenom : ");
	fgets(prenom, sizeof(prenom), stdin);

	// Supprimer le caractère de nouvelle ligne du dernier prénom saisi
	prenom[strcspn(prenom, "\n")] = 0;

	conversionPrenom(prenom);

	char cle[100];
	printf("Entrez votre cle : ");
	scanf("%s", cle);
	printf("\nVotes de l'électeur %s %s %s :\n\n",nom,prenom,cle);
	int bufferSize = SHA256_BLOCK_SIZE;
	char hashRes[bufferSize * 2 + 1];
	concatAndHash(nom, prenom, cle, hashRes);
	afficher_vote(filename,hashRes);
	exit (0);

}
