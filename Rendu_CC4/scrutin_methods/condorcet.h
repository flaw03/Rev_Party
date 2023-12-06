#ifndef __CONDORCET_H__
#define __CONDORCET_H__
#include "../utility_module/utils_tab.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief.
 * @param matriceDuel The duel matrix.
 * @param logfile : Pointer to the log file where votes are displayed.
 * @retrurn.
*/
int methode_Minimax(Matrice matriceDuel,FILE *logfile);


/**
 * @brief.
 * @param matriceDuel The duel matrix.
 * @param logfile : Pointer to the log file where votes are displayed.
 * @retrurn.
*/
int methode_Rangement_Des_Paires(Matrice matriceDuel,FILE *logfile);


/**
 * @brief.
 * @param matriceDuel The duel matrix.
 * @param logfile : Pointer to the log file where votes are displayed.
 * @retrurn.
*/
int methode_Schulze(Matrice matriceDuel,FILE *logfile);

#endif
