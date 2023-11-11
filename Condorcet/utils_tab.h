#ifndef __UTILS_TAB_H__
#define __UTILS_TAB_H__

typedef int* Colonne;
typedef Colonne * Tableau;

struct t_Matrice {
  int nb_ligne;
  int nb_colone;
  Tableau tableau;
};

typedef struct t_Matrice *Matrice;


Matrice create_Matrice(int nb_ligne, int nb_colonne);

void delete_Matrice(Matrice matrice);

void init_Matrice(Matrice matrice,int valeur);

void afficher_Matrice(Matrice matrice);



#endif