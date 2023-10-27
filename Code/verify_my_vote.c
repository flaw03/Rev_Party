#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <ctype.h>

#include "lecture_csv.c"
#include "Sha256/sha256.h"
#include "Sha256/sha256_utils.h"
#define STRLONG 30

/*
*     On compile avec gcc verify_my_vote.c Sha256/sha256.c Sha256/sha256_utils.c -o verify_my_vote
*     Et on lance le programme avec le fichier avec les votes en argv[1] et la cl� secr�te en argv[2], sinon ca va faire nimp
*/

/*
*    Fonction qui concat�ne nom, pr�nom et cl� et en fait un sha256
*/
void concatAndHash(char* nom, char* prenom, char* cle, char* hashRes) {
	char* resultat = (char*)malloc(sizeof(nom) + sizeof(prenom) + sizeof(cle) + 3);
	sprintf(resultat, "%s %s%s", nom, prenom, cle);
	char* item = malloc(STRLONG * sizeof(char));
	strcpy(item, resultat);
	sha256ofString((BYTE*)item, hashRes);
	free(item);
	free(resultat);

}

void verify_my_vote(CSVData* filename, char* hashRes) {
	/*
	*     On initialise les lignes pour i et les colonnes pour j
	*/
	int i = 1;
	int j = 3;

	/*q
	*    On trouve le sha dans le sha correspondant
	*/
	while ((strcmp(filename->data[i][j], hashRes) != 0) && i < filename->ligne)
		i++;

	/*
	*    On affiche les votes
	*/
	while (j < filename->colonne-1) {
		j++;
		printf("%s : %s\n", filename->data[0][j], filename->data[i][j]);
	}
}

/*
*    main pour tester
*/
int main(int argc, char** argv) {

	if (argc != 3) {
		fprintf(stderr,"Usage %s : fillname key\n",argv[0]);
		exit(1);
	}
	char nom[100];
	printf("Entrez votre nom : ");
	scanf("%s", nom);

	// Convertir en majuscules
	for (int i = 0; nom[i] != '\0'; i++) {
		nom[i] = toupper(nom[i]);
	}

	char prenom[100];
	printf("Entrez votre prenom : ");
	scanf("%s", prenom);

	// Convertir en majuscule la premi�re lettre
	prenom[0] = toupper(prenom[0]);

	int bufferSize = SHA256_BLOCK_SIZE;
	char hashRes[bufferSize * 2 + 1];
	concatAndHash(nom, prenom, argv[2], hashRes);
	const char* filename = argv[1];
	CSVData* data = lireCSV(filename);
	verify_my_vote(data,  hashRes);
	libererCSV(data);
	return 0;
}
