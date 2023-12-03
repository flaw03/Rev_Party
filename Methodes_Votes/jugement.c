#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


#include "Utiles.h"
#include "lecture.h"
#include "jugement.h"


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

double moyenne(int* tab,int taille){//Moyenne des votes sachant que si un vote == 0 , on ne le comptabilise pas
    double moy=0;
    bool isZero = false;
    int nbZero = 0;
    for(int i = 0;i<taille;i++){
        if(tab[i]==0){
            isZero = true;

        }
        moy+= tab[i];
    }
    if(isZero){
        taille-=nbZero;
    }
    return moy/taille;
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

Candidat* jugementMajoritaire(ListCand* lstCand,ListElect* lstElect,char* fichier,FILE* logfile){
    initJugement(lstCand,lstElect,fichier);
    trierVotes(lstCand,lstElect->size);
    Candidat* gagnant = NULL;
    int taille = lstElect->size;
    double verifMed = 0;
    double verifMoy = 0;
    fprintf(logfile,"\n\nDEBUT VERIFICATION JUGEMENT MAJORITAIRE\n\n");
    //comparer tous les candidats et leur médiane et prendre celui qui a le plus haut. Si il y a égalité entre 2 candidats, comparer la moyenne des candidats égaux
    for(Candidat* c = lstCand->head;c!=NULL;c=c->next){
        fprintf(logfile,"Candidat : %s\nvotes : ",c->prenom);
        afficherVote(c->jugement,taille,logfile);
        fprintf(logfile,"\nMoyenne : %f\nMediane : %f\n\n",moyenne(c->jugement,taille),mediane(c->jugement,taille));
        double valEtudiee = mediane(c->jugement,taille);
        if(valEtudiee<verifMed || verifMed == 0){
            verifMed=valEtudiee;
            gagnant = c;
        }
        else if(valEtudiee == verifMed){
            int moyenneEtudiee = moyenne(c->jugement,taille);
            if(moyenneEtudiee<verifMoy){
                gagnant = c;
                verifMoy=moyenneEtudiee;
            }
        }
    }
    return gagnant;

}


void voteJugementMajoritaireBallot(char* fichier,FILE* logfile){
    ListCand* lstCand = listCand_create();
    ListElect* lstElect = listElect_create();
    getCandidat(lstCand,fichier);
    int tab[lstCand->size];
    lstElect = getElecteur(lstElect,lstCand,fichier,tab);
    printf("\n************************************************************************************************");
    Candidat* gagnant = jugementMajoritaire(lstCand,lstElect,fichier,logfile);
    printf("\nJugement majoritaire, %d candidats, %d votants.\n\nVainqueur: %s\n",lstCand->size,lstElect->size,gagnant->prenom);
   printf("************************************************************************************************");

    printf("\n\n");
    tableauDelete(lstCand);
    listCand_delete(lstCand);
    listElect_delete(lstElect);

}



// int main(int argc,char** argv){
//     char* fichier = "../Data/jugement.csv";
//     // ListCand* lstCand = listCand_create();
//     // ListElect* lstElect = listElect_create();
    
//     voteJugementMajoritaireBallot(fichier,stdout);
//     // getCandidat(lstCand,fichier);
//     // int tab[lstCand->size];
//     // lstElect = getElecteur(lstElect,lstCand,fichier,tab);
//     // printf("taille:%d\n",lstElect->size);

//     // // initJugement(lstCand,lstElect,fichier);

    
//     // // trierVotes(lstCand,lstElect->size);
//     // // for(Candidat* c = lstCand->head;c!=NULL;c = c->next){
//     // //     printf("\nCandidat : %s :\n",c->prenom);
//     // //     for(int i = 0;i<lstElect->size;i++){
//     // //         printf("vote : %d ",c->jugement[i]);
//     // //     }
//     // // }

//     // //Candidat* top = lstCand->head;

//     // printf("\n\n*******************\n\n");
//     // jugementMajoritaire(lstCand,lstElect,fichier);

//     // // for(Candidat*c = lstCand->head;c!=NULL;c= c->next){
//     // //     printf("Candidat : %s \n",c->prenom);
//     // //     afficherVote(c->jugement,lstElect->size);
//     // //     printf("\n");
//     // //     printf("Moyenne : %f\n",moyenne(c->jugement,lstElect->size));
//     // //     printf("Mediane : %f\n",mediane(c->jugement,lstElect->size));
//     // //     printf("\n");
//     // // }

//     // printf("\n\n");
//     // tableauDelete(lstCand);
//     // listCand_delete(lstCand);
//     // listElect_delete(lstElect);
//     // printf("delete fini\n");

//     return 0;
// }
