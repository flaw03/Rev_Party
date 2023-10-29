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
*    Equipe 17 : NDOYE Assane, SMETS Yoann, JOSEPH Wilkens Marc Johnley, MORELLATO Adrian
*/

/*
*     On compile avec gcc verify_my_vote.c lecture_csv.c sha256.c sha256_utils.c -o verify_my_vote
*     Et on lance le programme avec juste ./verify_my_vote jugement.csv ou ./verify_my_vote VoteCondorcet.csv
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
	for (int i = 1; prenom[i] != '\0'; i++) {
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
	*     On initialise i pour les lignes et j pour les colonnes
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
		fprintf(stderr,"Il n'y a pas de hash correspondant à ce que vous avez saisi\n");
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
*    Fonction main
*/
int main(int argc, char** argv) {

	if (argc != 2) {
		fprintf(stderr, "Erreur, essayez avec ./verify_my_vote jugement.csv ou ./verify_my_vote VoteCondorcet.csv \n");
		exit (1);
	}
	
	const char* filename = argv[1];

	// On vérifie que le fichier passé en paramètre est bien en csv
	if (!isCSV(filename)){
		fprintf(stderr, "Erreur, le fichier en paramètre n'est pas un csv \n");
		exit(2);
	}

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

	int bufferSize = SHA256_BLOCK_SIZE;
	char hashRes[bufferSize * 2 + 1];
	concatAndHash(nom, prenom, cle, hashRes);
	CSVData data = createCSV();
	lireCSV(filename, data);
	verify_my_vote(data,  hashRes);
	exit (0);
}
