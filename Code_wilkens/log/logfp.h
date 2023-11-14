/*
	*Interace pour l'implantation du programme gerant le log du programme
*/

#ifndef __LOGFP_H__
#define __LOGFP_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>


/* 
  *open the login file and duplicate it on stdout 
  @param nom_fichier name of the file
 */

void ouvrirLog(const char* nom_fichier);

/*
	*close the login file
	@param desc : file descriptor
*/

void closeLog(int desc);

#endif