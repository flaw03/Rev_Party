#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "../utility_module/utiles.h"
#include "../utility_module/lecture_csv.h"
#include "uninominales.h"



struct s_Resultat {//Structure permettant d'avoir des résultats propres
    Candidat* candidat;
    double nb;
};




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
    fprintf(fichier,"\n\nVERIFICATION UNINOMINAL DEUX TOURS : \nPremier tour\n");
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
        if (votesEnCours == max2 && max2 != 0 && cand != second) {//Si il y a ex aequo avec le finaliste 2 , prendre le plus vieux
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
    fprintf(logfile,"---------------------------------------------------------------\n");
    fprintf(logfile,"Methode Uninomiale a 1 tours\n");
    ListElect* lstElect = listElect_create();
    ListCand* lstCand = listCand_create();
    lstCand = getCandidat(lstCand,fichier);
    Tableau tab = create_Tableau(lstCand->size);
    lstElect = getElecteur(lstElect,lstCand,fichier,tab);
    lstCand = initVote(lstElect,lstCand,logfile);
    Resultat victorieux = uninominal_un_tour(lstElect,lstCand,logfile);
    printf("Mode de Scrutin : Uninominal un tour :  %d candidats , %d votants",lstCand->size,lstElect->size);
    printf(",Vainqueur = %s, score : %f %%\n",victorieux.candidat->prenom,victorieux.nb);
    listElect_delete(lstElect);
    delete_Tableau(tab);
    listCand_delete(lstCand);
    return;
    
    
 }

 void deuxTours(FILE* logfile,char* fichier){
    fprintf(logfile,"---------------------------------------------------------------\n");
    fprintf(logfile,"Methode Uninomiale a 2 tours\n");
    ListElect* lstElect = listElect_create();
    ListCand* lstCand = listCand_create();

    lstCand = getCandidat(lstCand,fichier);

    Tableau tab = create_Tableau(lstCand->size);


    lstElect = getElecteur(lstElect,lstCand,fichier,tab);
    lstCand = initVote(lstElect,lstCand,logfile);
    float nbVotesTotaux = lstElect->size;
    Candidat** sec = finalistes_uninominal_deux_tours(lstElect,lstCand,logfile);

    if(sec[1]!=NULL){
        Candidat* elem1 = sec[0];
        Candidat* elem2 = sec[1];
        printf("Mode de Scrutin : Uninominal à deux tours, 1er tour, %d candidats, %d votants, vainqueur = %s, score : %f%%\n",lstCand->size,lstElect->size,elem1->nom,(elem1->vote/nbVotesTotaux)*100);
        printf("Mode de Scrutin : Uninominal à deux tours, 1er tour, %d candidats, %d votants, vainqueur = %s, score : %f%%\n",lstCand->size,lstElect->size,elem2->nom,(elem2->vote/nbVotesTotaux)*100);        
        elem1->vote = 0;
        elem2->vote = 0;
        ListElect* electeur2 = listElect_create();
        electeurs2ndTours2Candidats(electeur2,elem1,elem2,fichier,logfile);
        Resultat gagnant = uninominal_2nd_Tours(electeur2,sec,logfile);
        printf("Mode de Scrutin : Uninominal à deux tours, 2nd tour, 2 candidats, %d votants : Vainqueur = %s, score : %f %%\n",electeur2->size,gagnant.candidat->nom,gagnant.nb);
        listElect_delete(electeur2);
    }
    if(sec[1] == NULL){
        Candidat* majoritaire = sec[0];

        float pourcentage = (majoritaire->vote/nbVotesTotaux)*100;
         printf("Mode de Scrutin : Uninominal à deux tours, 1er tour, %d candidats,%d votants, vainqueur par majorité absolue = %s, score : %f%%.\n",lstCand->size,lstElect->size,majoritaire->nom,pourcentage);
    }
    listElect_delete(lstElect);
    delete_Tableau(tab);
    listCand_delete(lstCand);
    free(sec);
    return;
 }
