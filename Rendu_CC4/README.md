# Présentation du projet

Description du Projet :
Ce projet REV_Party est une application de vote qui prend en entrée un fichier CSV contenant des données de vote et effectue le calcul pour élire un candidat selon la méthode de vote de votre choix parmi celles disponibles.


## Table des Matières

1. [Tables des Matières](#table-des-matières)
2. [Fonctionnalités Principales](#fonctionnalités-principales)
3. [Utilisation](#utilisation)
4. [Exemple d'Utilisation](#exemple-dutilisation)
5. [Compilation](#compilation)
6. [Documentation](#documentation)
7. [Test](#test)
8. [Contributeur](#contributions)


## Fonctionnalités Principales :

1. Entrée des Données :
Le programme accepte deux types de fichiers CSV en tant qu'entrée. Le premier type contient des bulletins de vote, où chaque ligne représente un électeur et chaque colonne représente le choix de l'électeur pour un candidat. Le second type contient une matrice de duels, où chaque cellule indique le nombre de fois que le candidat de la ligne a été préféré au candidat de la colonne. L'utilisation du second type de fichier désactive l'option uni1, uni2, et jm.


2. Méthodes de Vote :
   
   2.1 Uninominal à un tour (uni1) : Chaque électeur vote pour un seul candidat, et le candidat avec le plus grand nombre de votes remporte l'élection.

   2.2 Uninominal à deux tours (uni2) : Les deux candidats avec le plus grand nombre de votes au premier tour passent au deuxième tour, où le candidat avec le plus grand nombre de votes est élu.

   2.3 Condorcet minimax (cm) : En quête d'un vainqueur selon la méthode de Condorcet, cette méthode, en l'absence d'un vainqueur évident, sélectionne le candidat gagnant en identifiant la paire de candidats présentant la marge de défaite potentielle la plus réduite. L'objectif est de minimiser le risque de subir la pire défaite possible.

   2.4 Condorcet Paires (cp) : En quête d'un vainqueur selon la méthode de Condorcet, cette approche, en l'absence de vainqueur évident, détermine le gagnant en comparant toutes les paires de candidats possibles. Le choix se porte sur le candidat qui remporte le plus grand nombre de duels individuels.

   2.5 Condorcet Schulze (cs) : À la recherche d'un vainqueur selon la méthode de Condorcet, cette méthode, en cas d'absence de vainqueur, sélectionne le gagnant en évaluant les marges de victoire dans les duels un contre un entre tous les candidats. Le choix se porte sur le candidat ayant les marges de victoire les plus fortes dans l'ensemble des comparaisons. Cette approche prend en considération la puissance relative des victoires individuelles pour déterminer le vainqueur.

   2.6 Jugement majoritaire (jm) : Le gagnant est déterminé en attribuant des jugements qualitatifs, puis en choisissant le candidat ayant la médiane la plus élevée . En cas d'égalité , on détermine la nouvelle mention majoritaire de ces candidats en enlevant le vote de l'électeur médian.

3. Options d'Affichage : 
L'application propose une option pour afficher les calculs intermédiaires dans un fichier log. Si l'option -o de la ligne de commande n'est pas mentionné , l'affichage se fera sur la sortir standard.

4. Programme indepandant verify_my_vote :
Cherche dans le fichier de votes, le vote correspondant au hash d’un votant , crypté avec son nom,prénom,clef secrète.
     

## Utilisation


1. Programme Principale *scrutin*

Pour exécuter le programme scrutin, utilisez la commande suivante :

```bash
bin/scrutin  -i <filename.csv>  | -d <filename.csv> -m {uni1, uni2, cm, cp, cs, jm, all} [-o <log_file>]
```

2. Programme indepandant *verify_my_vote*
   
Pour exécuter le programme indepandant verify_my_vote, utilisez la commande suivante :

```bash
bin/verify_my_vote <filename.csv> 
```




*Paramètres :*

-i : Spécifie le nom du fichier csv où se trouvent les ballots de vote.

-d : Spécifie le nom du fichier csv où se trouvent la matrice de duel.

-m : Sélectionne la méthode de vote (uni1, uni2, cm, cp, cs, jm, all).

-o : Optionnel. Spécifie le fichier log pour afficher les calculs intermédiaires.

*Note L'option -i et -d ne peuvent pas être présente en même temps*



## Exemple d'Utilisation 



1. Programme Principale *scrutin*

```bash
bin/uninominales -i donnees_votes.csv -m uni2 -o log.txt
```

Cette commande lance le programme avec le fichier CSV "donnees_votes.csv", utilise la méthode de vote uninominal à deux tours, et écrit les calculs dans le fichier log "log.txt".

2. Programme indepandant *verify_my_vote*
```bash
bin/verify_my_vote donnees_votes.csv
```


## Compilation

1. Programme Principale *scrutin*
   
Pour compiler le programme scrutin, exécutez la commande suivante :

```bash
make scrutin
```
2. Programme indepandant *verify_my_vote*
   
Pour compiler le programme indepandant verify_my_vote, exécutez la commande suivante :

```bash
make verify_my_vote
```

Pour compiler les 2 programme **scrutin** et **verify_my_vote**, exécutez la commande suivante :
```bash
make all
```


## Documentation

La documentation peut être générée en utilisant la commande suivante :

```bash
make doc
```

Vous pouvez consulter la documentation générée en ouvrant le fichier documentation/html/index.html dans votre navigateur web.


## Test



## Contributions

Equipe 17 :

NDOYE Assane 22100318

SMETS Yoann  22100213 

JOSEPH Wilkens Marc Johnley 22112190  

MORELLATO Adrian 22000859

*Remarque :*
*Assurez-vous que le fichier CSV est correctement formaté, avec les colonnes appropriées pour représenter les choix des électeurs.*
