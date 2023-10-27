#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <ctype.h>

#include "lecture_csv.h"
#include "sha256.h"
#include "sha256_utils.h"
#define STRLONG 30

/*
*     On compile avec gcc verify_my_vote.c sha256.c sha256_utils.c -o verify_my_vote
*     Et on lance le programme avec juste ./verify_my_vote
*/

/*
*    Fonction qui concatène nom, prénom et clé et en fait un sha256
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

void verify_my_vote(CSVData filename, char* hashRes) {
	/*
	*     On initialise les lignes pour i et les colonnes pour j
	*/
	int i = 1;
	int j = 3;

	/*
	*    On trouve le sha dans le sha correspondant
	*/
	while ((strcmp(filename->data[i][j], hashRes) != 0) && i < filename->ligne)
		i++;
	/*
	*    Condition si aucun hash n'est trouvé
	*/
	if (i == filename->ligne) {
		fprintf(stderr,"Ya pas de hash correspondant à ce que vous avez saisi\n");
		exit(2);
	}
	/*
	*    On affiche la ligne puis les votes de cette ligne
	*/
	for (int x = 0; x < filename->colonne; x++)
		printf("%s \t", filename->data[i][x]);
	
	while (j < filename->colonne-1) {
		j++;
		printf("\n%s : %s", filename->data[0][j], filename->data[i][j]);
	}
}

/*
*    main pour tester
*/
int main(int argc, char** argv) {

	if (argc != 1) {
		fprintf(stderr, "Erreur, essayez avec ./verify_my_vote \n");
		exit (1);
	}
	char nom[100];
	printf("Entrez votre nom : ");
	scanf("%s", nom);

	// Convertir en majuscules
	for (int i = 0; nom[i] != '\0'; i++)
		nom[i] = toupper(nom[i]);

	char prenom[100];
	printf("Entrez votre prenom : ");
	scanf("%s", prenom);

	// Convertir en majuscule la première lettre
	for (int i = 0; prenom[i] != '\0'; i++) {
		if (prenom[i] >= 'A' && prenom[i] <= 'Z')
			prenom[i] = tolower(prenom[i]);
	}
	prenom[0] = toupper(prenom[0]);

	char cle[100];
	printf("Entrez votre cle : ");
	scanf("%s", cle);

	printf("Saisissez un numéro correspondant au fichier dans lequel vous voulez vérifier votre vote : 1 pour jugement.csv ou 2 pour VoteCondorcet.csv ");
	char num[100];
	scanf("%s", num);
	while (num[0] != '1' && num[0] != '2') {
		printf("1 ou 2 j'ai dit\n");
		scanf("%s", num);
	}

	const char* filename;
	if (num[0] == '1')
		filename = "../Data/jugement.csv";
	else if (num[0] == '2')
		filename = "../Data/VoteCondorcet.csv";

	int bufferSize = SHA256_BLOCK_SIZE;
	char hashRes[bufferSize * 2 + 1];
	concatAndHash(nom, prenom, cle, hashRes);
	CSVData data = createCSV();
	lireCSV(filename, data);
	verify_my_vote(data,  hashRes);
	exit (0);
}
