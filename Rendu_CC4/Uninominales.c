 void deuxTours(FILE* logfile,char* fichier){

    ListElect* lstElect = listElect_create();
    ListCand* lstCand = listCand_create();

    lstCand = getCandidat(lstCand,fichier);
    int nb = lstCand->size;
    int tab[nb];

    lstElect = getElecteur(lstElect,lstCand,fichier,tab);
    lstCand = initVote(lstElect,lstCand,logfile);
    float nbVotesTotaux = lstElect->size;
    printf("uninominal à deux tours, tour 1, %d candidats, %d votants ",lstCand->size,lstElect->size);
    Candidat** sec = finalistes_uninominal_deux_tours(lstElect,lstCand,logfile);

    if(sec[1]!=NULL){
        printf(" vainqueur = %s, score : %f%%\n",sec[0]->nom,(sec[0]->vote/nbVotesTotaux)*100);
        printf("uninominal à deux tours, tour 1, %d candidats, %d votants , vainqueur = %s, score = %f%%\n",lstCand->size,lstElect->size,sec[1]->nom,(sec[1]->vote/nbVotesTotaux)*100);
        Candidat* elem1 = sec[0];
        Candidat* elem2 = sec[1];
        elem1->vote = 0;
        elem2->vote = 0;
        ListElect* electeur2 = listElect_create();
        electeurs2ndTours2Candidats(electeur2,elem1,elem2,fichier,logfile);
        Resultat gagnant = uninominal_2nd_Tours(electeur2,sec,logfile);
        printf("uninominal à deux tours : tour 2, 2 candidats, %d votants  : Vainqueur = %s, score : %f %%\n",lstElect->size,gagnant.candidat->nom,gagnant.nb);
        listElect_delete(electeur2);
    }
    if(sec[1] == NULL){
        Candidat* majoritaire = sec[0];

        float pourcentage = (majoritaire->vote/nbVotesTotaux)*100;
        printf("Nous avons un gagnant par majorité absolue ! \nLe gagnant est : %s %s possédant plus de %f%%  votes !.\n",majoritaire->nom,majoritaire->prenom,pourcentage);
    }
    listElect_delete(lstElect);
    listCand_delete(lstCand);
    free(sec);
    return;
 }
