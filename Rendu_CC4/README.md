# Méthodes uninominales à un et deux tours

Description du Projet :
Le projet est une application de vote uninominal qui prend en entrée un fichier CSV contenant des données de vote et effectue le calcul pour élire un candidat selon la méthode de vote de votre choix.


## Table des Matières

1. [Tables des Matières](#table-des-matières)
2. [Fonctionnalités Principales](#fonctionnalités-principales)
3. [Utilisation](#utilisation)
4. [Exemple d'Utilisation](#exemple-dutilisation)
5. [Compilation](#compilation)
6. [Documentation](#documentation)
7. [Contributeur](#contributions)


## Fonctionnalités Principales :

1. Entrée des Données : 
Le programme prend en entrée un fichier CSV contenant les données de vote. Chaque ligne du fichier représente un électeur, et chaque colonne représente le choix de l'électeur pour un candidat.

2. Méthodes de Vote :
   
    2.1 Uninominal à un tour (uni1) : Chaque électeur vote pour un seul candidat, et le candidat avec le plus grand nombre de votes remporte l'élection.

    2.2 Uninominal à deux tours (uni2) : Les deux candidats avec le plus grand nombre de votes au premier tour passent au deuxième tour, où le candidat avec le plus grand nombre de votes est élu.

   2.3 Condorcet minimax (cm) : Le gagnant est choisi en identifiant la paire de candidats avec la plus petite marge de défaite potentielle, visant ainsi à minimiser le risque de la pire défaite

   2.4 Condorcet Paires (cp) : Le gagnant est déterminé en comparant toutes les paires de candidats possibles et en sélectionnant celui qui remporte le plus grand nombre de duels un contre un
   
   2.5 Condorcet Schulze (cs) : Le gagnant est choisi en évaluant les marges de victoire dans les duels un contre un entre tous les candidats, puis en sélectionnant celui qui a les marges les plus fortes dans l'ensemble                                  des comparaisons. Cette méthode prend en compte la force relative des victoires dans les duels pour déterminer le vainqueur.

   2.6 Jugement majoritaire (jm) : Le gagnant est déterminé en attribuant des jugements qualitatifs, puis en choisissant le candidat ayant la médiane la plus élevée

4. Options d'Affichage : 
L'application propose une option pour afficher les calculs intermédiaires dans un fichier log.


## Utilisation


Pour exécuter le programme indepandant verify_my_vote, utilisez la commande suivante :

```bash
bin/verify_my_vote <filename.csv> 
```


Pour exécuter le programme scrutin, utilisez la commande suivante :

```bash
bin/scrutin  -i <filename.csv>  | -d <filename.csv> -m {uni1, uni2, cm, cp, cs, jm, all} [-o <log_file>]
```



*Paramètres :*

-i : Spécifie le nom du fichier csv où se trouvent les ballots de vote.

-d : Spécifie le nom du fichier csv où se trouvent la matrice de duel.

-m : Sélectionne la méthode de vote (uni1, uni2, cm, cp, cs, jm, all).

-o : Optionnel. Spécifie le fichier log pour afficher les calculs intermédiaires.

*Note*
*L'option -i et -d ne peuvent pas être présente en même temps*



## Exemple d'Utilisation 

```bash
bin/uninominales -i donnees_votes.csv -m uni2 -o log.txt
```

Cette commande lance le programme avec le fichier CSV "donnees_votes.csv", utilise la méthode de vote uninominal à deux tours, et écrit les calculs dans le fichier log "log.txt".


## Compilation

Pour compiler le programme scrutin, exécutez la commande suivante :

```bash
make scrutin
```

Pour compiler le programme indepandant verify_my_vote, exécutez la commande suivante :

```bash
make verify_my_vote
```

## Documentation

La documentation peut être générée en utilisant la commande suivante :

```bash
make doc
```

Vous pouvez consulter la documentation générée en ouvrant le fichier documentation/html/index.html dans votre navigateur web.


## Contributions

Equipe 17 :

NDOYE Assane 22100318

SMETS Yoann  22100213 

JOSEPH Wilkens Marc Johnley 22112190  

MORELLATO Adrian 22000859

*Remarque :*
*Assurez-vous que le fichier CSV est correctement formaté, avec les colonnes appropriées pour représenter les choix des électeurs.*
