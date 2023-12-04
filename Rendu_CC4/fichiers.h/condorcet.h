#ifndef __CONDORCET_H__
#define __CONDORCET_H__
#include "utils_tab.h"
#include <stdio.h>
#include <stdlib.h>


int methode_Minimax(Matrice matriceDuel,FILE *logfile);

int methode_Rangement_Des_Paires(Matrice matriceDuel,FILE *logfile);

int methode_Schulze(Matrice matriceDuel,FILE *logfile);

#endif
