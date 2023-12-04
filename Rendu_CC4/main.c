#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

<<<<<<< HEAD
#include "inc/Utiles.h"
#include "inc/lecture_csv.h"
#include "inc/uninominales.h"
#include "inc/utils_tab.h"
#include "inc/condorcet.h"
#include "inc/jugement.h"

/**
 *	@defgroup Main Test program for Uninominales Implantation
 *  @brief Definition of the Uninominales type and operators
 *  @{
 */


/** Print a usage message for this program.
 
 @code{.unparsed}
 $bin/uninominales -i <filename.csv> | -d <nomFichierCSV> [-o <log_file>] -m {uni1, uni2, all, cm, cp, cs)}

Options :
  -i <filename.csv> > : Traite le fichier CSV spécifié.
  -d <filename.csv> > : Traite le fichier CSV spécifié.
  -o <<filename.csv> >    : Spécifie le fichier de log (optionnel).
  -m <methode>        : Précise la méthode de scrutin à utiliser.

Notez que la commande doit contenir soit -i ou -d, mais pas les deux en même temps.
 
 @endcode
 */

//Compile with : make



int main(int argc, char** argv) {
    int opt;
    char* filename = NULL;
    char* fichierLog = NULL;
    bool optionBalot = false;
    bool optionAll = false;
    bool optionMatrice = false;
    bool optvalide = false;
    char* methode = NULL;
    Matrice matriceDuel = NULL;
    FILE* logfile = stdout;
    int nbrElecteur;
=======
#include "../Rendu_CC4/fichiers.h/Utiles.h"
#include "../Rendu_CC4/fichiers.h/lecture.h"
#include "../Rendu_CC4/fichiers.h/Uninominales.h"



struct s_Resultat {//Structure permettant d'avoir des résultats propres
    Candidat* candidat;
    double nb;
};
>>>>>>> d66c439d258a13975e994dbc15b2d863aff897bc




Resultat affecter_resultat(Candidat* candidat,double nb){ 
    Resultat result;
    result.candidat = candidat;
    result.nb = nb;
    return result;
}

ListCand* initVote(ListElect *lstElect , ListCand* lstCand,FILE* fichier){ 
    for(Candidat* c = lstCand->head;c!=NULL;c = c->next){ //On remet tous les votes à 0 en prévision d'un prochain tour
         c->vote = 0;
     }
    fprintf(fichier,"\n\nVERIFICATION INITIALISATION DES VOTES \n");
    for(Electeur* e = lstElect->head;e!=NULL;e = e->next){ //Parcours la liste des électeurs et on incrémente le vote du candidat associé
        e->candidat->vote ++;
        fprintf(fichier,"Electeur : %s a vote pour %s\n",e->prenom,e->candidat->prenom);
        }

    return lstCand;
}




Resultat uninominal_un_tour(ListElect *lstElect, ListCand *lstCand,FILE* fichier){//Parcours tous les candidats et ressort celui qui a le plus de votes
    float nbVotesTotaux =lstElect->size;
    
<<<<<<< HEAD
    if(argc<5){
            fprintf(stderr, "Usage: %s -i <filename.csv> | -d <filename.csv> -m {uni1, uni2, cm, cp, cs,jm, all} [-o <log_file>]\n", argv[0]);
            exit(9);
        }
    while ((opt = getopt(argc, argv, "i:o:m:d:")) != -1) {
        switch (opt) {
            case 'i':
                filename= optarg;
                nbrElecteur = lireBallot(filename,&matriceDuel);
                optionBalot = true;
                break;
            case 'd':
                filename = optarg;
                nbrElecteur = lireMatriceDuel(filename,&matriceDuel);
                optionMatrice = true;
                break;
            case 'o':                       
                fichierLog = optarg;
                logfile = fopen(fichierLog, "w");
                if (logfile == NULL) {
                    printf("erreur fichier.\n");
                    exit(33);
                }
                break;
            case 'm':
                methode = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s -i <filename.csv>  | -d <filename.csv> -m {uni1, uni2, cm, cp, cs,jm, all} [-o <log_file>]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    if ((optionBalot && optionMatrice) || (!optionMatrice && !optionBalot) ) {
        fprintf(stderr, "Erreur : Les options -i et -d ne peuvent pas être présentes simultanément.\n");
        exit(EXIT_FAILURE);
    }
    if (methode == NULL){
        fprintf(stderr, "Usage: %s -i <filename.csv>  | -d <filename.csv> -m {uni1, uni2, cm, cp, cs,jm, all} [-o <log_file>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if (strcmp(methode,"all") == 0){
        optionAll = true;
        optvalide = true;
    }

    if((strcmp(methode,"uni1") == 0  || optionAll ) && optionBalot){
        unTour(filename,logfile);    
        optvalide = true;
        
    }
    if((strcmp(methode,"uni2" )==0   || optionAll) && optionBalot){
        deuxTours(logfile,filename);
        optvalide = true;
    }
    if(strcmp(methode,"cm")==0 || optionAll ){
        int vainqueur = methode_Minimax(matriceDuel,logfile);
        char * nomVainqueur = obtenir_nom_Candidat(filename,vainqueur,optionBalot);
        printf("Mode de Scrutin : Condorcet Minimax, %d candidats, %d votants, vainqueur = %s\n",matriceDuel->nb_colonne,
        nbrElecteur,nomVainqueur);
        free(nomVainqueur);
        optvalide = true;

    }

    if(strcmp(methode,"cp") ==0 || optionAll ){
        int vainqueur = methode_Rangement_Des_Paires(matriceDuel,logfile);
        char * nomVainqueur = obtenir_nom_Candidat(filename,vainqueur,optionBalot);
        printf("Mode de Scrutin : Condorcet paires, %d candidats, %d votants, vainqueur = %s\n",matriceDuel->nb_colonne,
        nbrElecteur,nomVainqueur);
        free(nomVainqueur);
        optvalide = true;

    }

    if(strcmp(methode,"cs") ==0 || optionAll){
        int vainqueur = methode_Schulze(matriceDuel,logfile);
        char * nomVainqueur = obtenir_nom_Candidat(filename,vainqueur,optionBalot);
        printf("Mode de Scrutin : Condorcet Shulze, %d candidats, %d votants, vainqueur = %s\n",matriceDuel->nb_colonne,
        nbrElecteur,nomVainqueur);
        free(nomVainqueur);
        optvalide = true;

    }

    if((strcmp(methode,"jm") == 0 || optionAll) && optionBalot){
        voteJugementMajoritaireBallot(filename,logfile);
        optvalide = true;
    }
    
    if (!optvalide){
        fprintf(stderr, "Usage: %s -i <filename.csv>  | -d <filename.csv> -m {uni1, uni2, cm, cp, cs,jm, all} [-o <log_file>]\n", argv[0]);
        exit(EXIT_FAILURE);
=======
    Candidat* gagnant = NULL;
    int max = 0;
    fprintf(fichier,"\n\n VERIFICATION UNINOMINAL UN TOUR \n-");
    for(Candidat* cand = lstCand->head; cand!=NULL;cand = cand->next){ 
        int votesEnCours = cand->vote;
        fprintf(fichier,"Candidat en cours : %s %s , Nombre de votes pour ce candidat : %d\n",cand->nom,cand->prenom,votesEnCours);
        if(votesEnCours>max){
            max = votesEnCours;
            gagnant = cand;
        }
        if(votesEnCours==max && max != 0){ //Si il y a ex aecquo , prendre le plus vieux.
            if((cand->age)>(gagnant->age)){
                gagnant = cand;
            }
        }
    }
    float pourcentage = (max/nbVotesTotaux)*100;
    Resultat result = affecter_resultat(gagnant,pourcentage);
    return result;
}

Candidat ** createRetour(Candidat** tab,Candidat* candidat){ //Mise en forme
    tab[0] = candidat;
    tab[1] = NULL;
    return tab;

}

Candidat** finalistes_uninominal_deux_tours(ListElect *lstElect, ListCand *lstCand,FILE* fichier){ //Récupère les 2 finalistes d'un vote uninominal à 2 tours
    int nbVotesTotaux = lstElect->size;
    double majorite = nbVotesTotaux/2;
    int max1 = 0;
    int max2 = 0;
    Candidat* first = NULL;
    Candidat* second = NULL;
    Candidat** finalistes = malloc(2*sizeof(Candidat));
    Candidat* cand = lstCand->head;
    fprintf(fichier,"\n\nVERIFICATION UNINOMINAL DEUX TOURS : \n-Premier tour\n-");
    while(cand!=NULL){ //Parcours de la liste de candidats
        int votesEnCours = cand->vote; 
        fprintf(fichier,"Candidat : %s %s , nombre de votes : %d\n",cand->nom,cand->prenom,votesEnCours);
        if(votesEnCours > max1){ //Récupère les 2 candidats ayant le plus de voix
            max2 = max1;
            second = first;
            max1 = votesEnCours;
            first = cand;
        }
        else if(votesEnCours > max2){
            max2 = votesEnCours;
            second = cand;
        }
        if (votesEnCours == max1 && max1 != 0 && cand != first) { //Si il y a ex aequo avec le finaliste 1 , prendre le plus vieux
            if ((cand->age > first->age)) {
                first = cand;
            }
        }
        if (votesEnCours == max2 && max2 != 0 && cand != second) {//Si il y a ex aequo avec le finaliste 1 , prendre le plus vieux
            if ((cand->age > second->age)) {
                second = cand;
             }
        }

        if(votesEnCours>majorite){ // Si un candidat détient la majoritée absolue, il est renvoyé.
            return createRetour(finalistes,cand);
        }
        cand = cand->next;
    }
    if(first != NULL && second != NULL){
        finalistes[0] = first;
        finalistes[1] = second;
    }
    return finalistes; //Retourne le tableau contenant les 2 candidats finalistes
}

Resultat uninominal_2nd_Tours(ListElect* lstElecteurs, Candidat** finalistes,FILE* logfile){
    Resultat result;
    Candidat* cand1 = finalistes[0];
    Candidat* cand2 = finalistes[1];
    double votesCandidats1 = cand1->vote;
    double votesCandidats2 = cand2->vote;
    double votes = lstElecteurs->size;
    fprintf(logfile,"\n\nVERIF 2ND TOUR : \n-Candidat %s %s a %d votes\n Candidat %s %s a %d votes\n",cand1->prenom,cand1->nom,cand1->vote,cand2->prenom,cand2->nom,cand2->vote);
    if(votesCandidats1>votesCandidats2){ //Retourne le candidat ayant le plus de votes
        result.candidat = finalistes[0];
        result.nb = (votesCandidats1/votes)*100;
    }
    else{
        result.candidat = finalistes[1];
        result.nb = (votesCandidats2/votes)*100;
>>>>>>> d66c439d258a13975e994dbc15b2d863aff897bc
    }
    return result;
}

 ListElect* createTest(ListElect* lstElect, ListCand* lstCand,int nbTest){ //Permet d'instancier des tests avec un nombre voulu
                                                                           //En ayant déjà crée des candidats
    srand(time(NULL));

    Candidat* candidats[lstCand->size];
    int taille = 0;
    for(Candidat* cand = lstCand->head;cand != NULL;cand = cand->next){
        candidats[taille] = cand;
        taille++;
    }


    for(int i = 0;i<nbTest;i++){
        int choice = rand()%lstCand->size;
        Electeur* createTest = create_electeur("Nom","Prenom",candidats[choice]);
        list_add_Electeur(lstElect,createTest);
    }
    return lstElect;
 }

 void unTour(char* fichier,FILE *logfile){
    ListElect* lstElect = listElect_create();
    ListCand* lstCand = listCand_create();
    lstCand = getCandidat(lstCand,fichier);
    int nb = lstCand->size;
    int tab[nb];
    lstElect = getElecteur(lstElect,lstCand,fichier,tab);
    lstCand = initVote(lstElect,lstCand,logfile);
    Resultat victorieux = uninominal_un_tour(lstElect,lstCand,logfile);
    printf("uninominal un tour :  %d candidats , %d votants",lstCand->size,lstElect->size);
    printf(" ,vainqueur = %s, score : %f %%\n",victorieux.candidat->prenom,victorieux.nb);
    listElect_delete(lstElect);
    listCand_delete(lstCand);
    return;
    
    
 }

 void deuxTours(FILE* logfile,char* fichier){

    ListElect* lstElect = listElect_create();
    ListCand* lstCand = listCand_create();

    lstCand = getCandidat(lstCand,fichier);
    int nb = lstCand->size;
    int tab[nb];

    lstElect = getElecteur(lstElect,lstCand,fichier,tab);
    lstCand = initVote(lstElect,lstCand,logfile);
    float nbVotesTotaux = lstElect->size;
    printf("Mode de scrutin : uninominal à deux tours, tour 1, %d candidats, %d votants ",lstCand->size,lstElect->size);
    Candidat** sec = finalistes_uninominal_deux_tours(lstElect,lstCand,logfile);

    if(sec[1]!=NULL){
        printf(" vainqueur = %s, score : %f%%\n",sec[0]->nom,(sec[0]->vote/nbVotesTotaux)*100);
        printf("Mode de scrutin : uninominal à deux tours, tour 1, %d candidats, %d votants , vainqueur = %s, score = %f%%\n",lstCand->size,lstElect->size,sec[1]->nom,(sec[1]->vote/nbVotesTotaux)*100);
        Candidat* elem1 = sec[0];
        Candidat* elem2 = sec[1];
        elem1->vote = 0;
        elem2->vote = 0;
        ListElect* electeur2 = listElect_create();
        electeurs2ndTours2Candidats(electeur2,elem1,elem2,fichier,logfile);
        Resultat gagnant = uninominal_2nd_Tours(electeur2,sec,logfile);
        printf("Mode de scrutin : uninominal à deux tours : tour 2, 2 candidats, %d votants  : Vainqueur = %s, score : %f %%\n",lstElect->size,gagnant.candidat->nom,gagnant.nb);
        listElect_delete(electeur2);
    }
    if(sec[1] == NULL){
        Candidat* majoritaire = sec[0];

        float pourcentage = (majoritaire->vote/nbVotesTotaux)*100;
        printf("Mode de scrutin : uninominal à deux tours , tour 1, %d candidats, %d votant , vainqueur = %s ,score = %f%%\n",lstCand->size,lstElect->size,majoritaire->prenom,pourcentage);
    }
    listElect_delete(lstElect);
    listCand_delete(lstCand);
    free(sec);
    return;
 }

