#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "Utiles.c"


typedef struct{//Structure permettant d'avoir des résultats propres
    Candidat* candidat;
    double nb;
} Resultat;



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
    
    Candidat* gagnant;
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
    fprintf(fichier,"\n\n VERIFICATION UNINOMINAL DEUX TOURS \n-");
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
    fprintf(logfile,"\n\nVERIF 2ND TOURS : \n-Candidat %s %s a %d votes\n Candidat %s %s a %d votes",cand1->prenom,cand1->nom,cand1->vote,cand2->prenom,cand2->nom,cand2->vote);
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

int main(int argc,char** argv){

    FILE* logfile = fopen("log.txt","w");
    ListElect* lstElect = listElect_create();
    ListCand* lstCand = listCand_create();

    Candidat* c1 = create_candidat("Jean-Marie","LEPEN",139);
    Candidat* c2 = create_candidat("MOnsieur","BIgard",812);
    Candidat* c3 = create_candidat("Madame","Pavochko",203);
    listCand_add(lstCand,c1);
    listCand_add(lstCand,c2);
    listCand_add(lstCand,c3);
    


    ListElect* test = listElect_create();
    int nb;
    printf("Combien de données de test voulez vous ? \nVeuillez insérer un nombre : ");
    scanf("%d",&nb);

    test = createTest(test,lstCand,nb);
    float nbVotesTotaux = test->size;
    lstCand = initVote(test,lstCand,logfile);
    for(Candidat* c = lstCand->head;c!=NULL;c = c->next){
        printf("CAndidat : %s a %d votes\n",c->prenom,c->vote);
    }


    Resultat victorieux = uninominal_un_tour(test,lstCand,logfile);
    printf("Vote uninominal un tour :\n");
    printf("Le gagnant au vote uninominal un tour est : %s avec %f %% votes\n",victorieux.candidat->prenom,victorieux.nb);
    printf("\nVote uninominal deux tours :\n");
    Candidat** sec = finalistes_uninominal_deux_tours(test,lstCand,logfile);
    if(sec[1]!=NULL){
        printf("les finalistes sont : \n-%s \n-%s\n",sec[0]->nom,sec[1]->nom);
        Resultat gagnant = uninominal_2nd_Tours(test,sec,logfile);
        printf("Le gagnant du vote uninominal 2nd tours est : %s avec %f %% votes\n",gagnant.candidat->nom,gagnant.nb);
    }
    if(sec[1] == NULL){
        Candidat* majoritaire = sec[0];

        float pourcentage = (majoritaire->vote/nbVotesTotaux)*100;
        printf("MAJORITAIRE !!!! \nLe gagnant est : %s %s possédant plus de %f%%  votes !.\n",majoritaire->nom,majoritaire->prenom,pourcentage);
    }

    free(sec);
    listElect_delete(lstElect);
    listCand_delete(lstCand);
    listElect_delete(test);
    fclose(logfile);

    return 0;
}