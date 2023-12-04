#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


#include "../Rendu_CC4/fichiers.h/Utiles.h"
#include "../Rendu_CC4/fichiers.h/lecture.h"
#include "../Rendu_CC4/fichiers.h/jugement.h"


void trier(int* tab,int taille){
    for(int i = 0;i<taille;i++){
        for(int j = 0;j<taille;j++){
            if(tab[i]>tab[j]){
                int temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }

}

void trierVotes(ListCand* lstCand,int taille){
    for(Candidat* c = lstCand->head;c!=NULL;c = c->next){
        trier(c->jugement,taille);
    }
}

int assocMention(int i){
    int retour = 0;
    if(i==1 || i == 3 || i == 5 || i == 7 || i == 9){
        retour= 1;
    }
    else if(i==2 || i == 4 || i == 6 || i == 8){
        retour=2;
    }
    return retour;
}

int calculerChemin(int *tab,int taille){
    int mid;
    if(taille%2 == 0){
        mid = (taille/2)-1;
    }
    else{
        mid = taille/2;
    }
    int mention = tab[mid]; //mediane
    int addMention = assocMention(mention); //distance jusqu'à la prochaine mention
    int cpt = 0;
    int recherche = mention+addMention;

    while(mention != recherche){
        mid--;
        mention = tab[mid];
        cpt++;
    }
    return cpt;

}

double mediane(int* tab,int taille){
    int verif = taille%2;
    if(verif == 0){
        int mid = (taille/2)-1;
        return tab[mid];
    }
    else{
        int mil = (taille/2);
        return tab[mil];
    }
}

void afficherVote(int* tab,int taille,FILE* logfile){
    for(int i = 0;i<taille;i++){
        fprintf(logfile,"[");
        fprintf(logfile,"%d",tab[i]);
        fprintf(logfile,"]");
    }
}


void affichage(FILE* logfile,Candidat* c,int taille){
    fprintf(logfile,"Candidat : %s\nvotes : ",c->prenom);
    afficherVote(c->jugement,taille,logfile);
    fprintf(logfile,"\nMediane : %f\n\n",mediane(c->jugement,taille));

}

Candidat* jugementMajoritaire(ListCand* lstCand,ListElect* lstElect,char* fichier,FILE* logfile){
    initJugement(lstCand,lstElect,fichier);
    trierVotes(lstCand,lstElect->size);
    Candidat* gagnant = NULL;
    int taille = lstElect->size;
    double verifMed = -1;
    fprintf(logfile,"\n\nDEBUT VERIFICATION JUGEMENT MAJORITAIRE\n\n");
    affichage(logfile,lstCand->head,taille);
    //comparer tous les candidats et leur médiane et prendre celui qui a le plus haut.
    for(Candidat* c = lstCand->head->next;c!=NULL;c=c->next){
        affichage(logfile,c,taille);
        double valEtudiee = mediane(c->jugement,taille);
        if(valEtudiee<verifMed || verifMed == -1){
            verifMed=valEtudiee;
            gagnant = c;
        }
        //Egalite entre 2 médianes => itération en enlevant un électeur et recalculant les chemins
        else if(valEtudiee == verifMed){
            fprintf(logfile,"Egalite entre 2 médianes pour les candidats %s et %s , calculons la distance jusqu'à la mention précédente..\n",gagnant->prenom,c->prenom);
            int cheminGagnant = calculerChemin(gagnant->jugement,taille);
            int cheminCandCourant = calculerChemin(c->jugement,taille);
            if(cheminCandCourant>cheminGagnant){
                gagnant = c;
                verifMed = valEtudiee;
            }
            else if(cheminCandCourant==cheminGagnant){
                fprintf(logfile,"Egalite entre 2 chemins pour les candidats %s et %s , passons à la mention précédente..\n",gagnant->prenom,c->prenom);
                int cheminGagnantv2 = cheminGagnant;
                int cheminCourantv2 = cheminCandCourant;
                double med2 = valEtudiee;
                double med1 = verifMed;
                do{
                    cheminGagnantv2 = calculerChemin(gagnant->jugement,(taille+1));
                    cheminCourantv2 = calculerChemin(c->jugement,(taille+1));
                    med1 = mediane(gagnant->jugement,taille+1);
                    med2 = mediane(c->jugement,taille+1);
            }while(med1==med2 && cheminCourantv2==cheminGagnantv2);
            if(cheminCourantv2>cheminGagnantv2|| med2<med1){
                        gagnant = c;
                        verifMed = valEtudiee;
                    }
            }
        }
    }
    Candidat* first= lstCand->head;
    if(mediane(first->jugement,taille)<mediane(gagnant->jugement,taille)){
        gagnant = first;
    }

    fprintf(logfile,"Fin. Candidat majoritairement élu est : %s",gagnant->prenom);
    return gagnant;

}


void voteJugementMajoritaireBallot(char* fichier,FILE* logfile){
    ListCand* lstCand = listCand_create();
    ListElect* lstElect = listElect_create();
    getCandidat(lstCand,fichier);
    int tab[lstCand->size];
    lstElect = getElecteur(lstElect,lstCand,fichier,tab);

    Candidat* gagnant = jugementMajoritaire(lstCand,lstElect,fichier,logfile);
    printf("Jugement majoritaire : %d candidats, %d votants, Vainqueur = %s\n",lstCand->size,lstElect->size,gagnant->prenom);

    tableauDelete(lstCand);
    listCand_delete(lstCand);
    listElect_delete(lstElect);

}
