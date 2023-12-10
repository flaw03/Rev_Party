#ifndef __CONDORCET_H__
#define __CONDORCET_H__

#include "../utility_module/utils_tab.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Applique la méthode Minimax pour résoudre une élection de Condorcet.
 *
 * Cette méthode vise à trouver un vainqueur de Condorcet. Si aucun vainqueur n'est trouvé, elle sélectionne le candidat avec la plus petite marge de défaite potentielle.
 *
 * @param matriceDuel La matrice des duels.
 * @param logfile Pointeur vers le fichier journal où les résultats sont affichés.
 * @return Le vainqueur de Condorcet .
 */
int methode_Minimax(Matrice matriceDuel, FILE *logfile);

/**
 * @brief Applique la méthode de tri des paires pour résoudre une élection de Condorcet.
 *
 * Cette méthode vise à trouver un vainqueur de Condorcet. Si aucun vainqueur n'est trouvé, elle sélectionne le candidat en comparant toutes les paires possibles de candidats et en choisissant celui qui remporte le plus grand nombre de victoires par paires.
 *
 * @param matriceDuel La matrice des duels.
 * @param logfile Pointeur vers le fichier journal où les résultats sont affichés.
 * @return Le vainqueur de Condorcet.
 */ 
int methode_Rangement_Des_Paires(Matrice matriceDuel, FILE *logfile);

/**
 * @brief Applique la méthode Schulze pour résoudre une élection de Condorcet.
 *
 * Cette méthode vise à trouver un vainqueur de Condorcet. Si aucun vainqueur n'est trouvé, elle sélectionne le candidat en évaluant les marges de victoire dans les duels un contre un entre tous les candidats et en choisissant celui qui a les marges les plus fortes dans l'ensemble des comparaisons.
 *
 * @param matriceDuel La matrice des duels.
 * @param logfile Pointeur vers le fichier journal où les résultats sont affichés.
 * @return Le vainqueur de Condorcet.
 */
int methode_Schulze(Matrice matriceDuel, FILE *logfile);

#endif
