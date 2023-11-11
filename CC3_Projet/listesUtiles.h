#ifndef LISTESUTILES_H
#define LISTESUTILES_H


typedef struct s_List_Cand ListCand;
typedef struct s_List_Electeur ListElect;
typedef struct s_Candidat Candidat;
typedef struct s_Electeur Electeur;

Electeur* create_electeur(const char* nom, const char* prenom, Candidat* candidat);
ListElect* listElect_create();
ListElect* list_add_Electeur(ListElect* l, Electeur* electeur);
void listElect_delete(ListElect* l);

Candidat* create_candidat(const char* nom, const char* prenom, int age);
ListCand* listCand_create();
ListCand* listCand_add(ListCand* l, Candidat* candidat);
void listCand_delete(ListCand* l);
#endif