#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "listesUtiles.c"



typedef struct{
    Candidat* candidat;
    int nb;
} Resultat;



Resultat affecter_resultat(Candidat* candidat,int nb){
    Resultat result;
    result.candidat = candidat;
    result.nb = nb;
    return result;
}

int nbVotes(ListElect *lstElect , Candidat* candidat){ //Calcul nombre vote d'un candidat
    int votes=0;
    for(Electeur* e = lstElect->head;e!=NULL;e = e->next){
        if(e->candidat == candidat){
            votes++;
        }
    }
    return votes;
}


Resultat uninominal_un_tour(ListElect *lstElect, ListCand *lstCand){
    float nbVotesTotaux =lstElect->size;
    int max = 0;
    Candidat* gagnant;
    for(Candidat* cand = lstCand->head; cand!=NULL;cand = cand->next){ //Parcours tous les candidats et ressort celui qui a le plus de votes
        int votesEnCours = nbVotes(lstElect,cand);
        if(votesEnCours>max){
            max = votesEnCours;
            gagnant = cand;
        }
        if(votesEnCours==max && max != 0){
            if((cand->age)>(gagnant->age)){
                gagnant = cand;
            }
        }
    }
    int pourcentage = (max/nbVotesTotaux)*100;
    Resultat result = affecter_resultat(gagnant,pourcentage);
    return result;
}

Candidat ** createRetour(Candidat** tab,Candidat* candidat){ //Mise en forme
    tab[0] = candidat;
    tab[1] = NULL;
    return tab;

}

Candidat** finalistes_uninominal_deux_tours(ListElect *lstElect, ListCand *lstCand){
    int nbVotesTotaux = lstElect->size;
    float majorite = nbVotesTotaux/2;
    int max1 = 0;
    int max2 = 0;
    Candidat* first = NULL;
    Candidat* second = NULL;

    Candidat** finalistes = malloc(2*sizeof(Candidat));

    Candidat* cand = lstCand->head;
    while(cand!=NULL){ //Parcours de la liste de candidats
        int votesEnCours = nbVotes(lstElect,cand); 
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
        if (votesEnCours == max1 && max1 != 0 && cand != first) { //Si il y a ex aequo , prend le plus vieux
            if ((cand->age > first->age)) {
                first = cand;
            }
        }
        if (votesEnCours == max2 && max2 != 0 && cand != second) {
            if ((cand->age > second->age)) {
                second = cand;
             }
        }

        if(votesEnCours>majorite){ // Si un candidat détient la majorité absolue, il est renvoyé.
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

Resultat uninominal_2nd_Tours(ListElect* lstElecteurs, Candidat** finalistes){
    Resultat result;
    int votesCandidats1 = nbVotes(lstElecteurs,finalistes[0]);
    int votesCandidats2 = nbVotes(lstElecteurs,finalistes[1]);

    if(votesCandidats1>votesCandidats2){ //Retourne le candidat ayant le plus de votes
        result.candidat = finalistes[0];
        result.nb = votesCandidats1;
    }
    else{
        result.candidat = finalistes[1];
        result.nb = votesCandidats2;
    }
    return result;
}

int main(int argc,char** argv){
    ListElect* lstElect = listElect_create();
    ListCand* lstCand = listCand_create();

    Candidat* c1 = create_candidat("Jean-Marie","LEPEN",139);
    Candidat* c2 = create_candidat("MOnsieur","BIgard",812);
    Candidat* c3 = create_candidat("Madame","Pavochko",203);
    listCand_add(lstCand,c1);
    listCand_add(lstCand,c2);
    listCand_add(lstCand,c3);

    Electeur* e1 = create_electeur("SMETS","Yoann",c3);
    Electeur* e2 = create_electeur("SMETS","Yoann",c2);
    Electeur* e3 = create_electeur("SMETS","Yoann",c2);
    Electeur* e4 = create_electeur("SMETS","Yoann",c3);
    Electeur* e5 = create_electeur("SMETS","Yoann",c1);
    Electeur* e6 = create_electeur("SMETS","Yoann",c3);
    Electeur* e7 = create_electeur("SMETS","Yoann",c1);
    Electeur* e8 = create_electeur("SMETS","Yoann",c1);
    Electeur* e9 = create_electeur("SMETS","Yoann",c2);
    Electeur*e10 = create_electeur("SMETS","Yoann",c3);
    list_add_Electeur(lstElect,e1);
    list_add_Electeur(lstElect,e2);
    list_add_Electeur(lstElect,e3);
    list_add_Electeur(lstElect,e4);
    list_add_Electeur(lstElect,e5);
    list_add_Electeur(lstElect,e6);
    list_add_Electeur(lstElect,e7);
    list_add_Electeur(lstElect,e8);
    list_add_Electeur(lstElect,e9);
    list_add_Electeur(lstElect,e10);
    
    Resultat victorieux = uninominal_un_tour(lstElect,lstCand);
    printf("Vote uninominal un tour :\n");
    printf("Le gagnant au vote uninominal un tour est : %s avec %d %% votes\n",victorieux.candidat->prenom,victorieux.nb);
    printf("\nVote uninominal deux tours :\n");
    Candidat** sec = finalistes_uninominal_deux_tours(lstElect,lstCand);
    if(sec[1]!=NULL){
        printf("les finalistes sont : \n-%s \n-%s\n",sec[0]->nom,sec[1]->nom);
        Resultat gagnant = uninominal_2nd_Tours(lstElect,sec);
        printf("Le gagnant du vote uninominal 2nd tours est : %s avec %d votes\n",gagnant.candidat->nom,gagnant.nb);
    }
    if(sec[1] == NULL){
        printf("MAJORITAIRE !!!! %s\n",sec[0]->nom);
    }

    free(sec);
    listCand_delete(lstCand);
    listElect_delete(lstElect);

    return 0;
}