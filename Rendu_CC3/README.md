# Méthodes uninominales à un et deux tours

Description du Projet :
Le projet est une application de vote uninominal qui prend en entrée un fichier CSV contenant des données de vote et effectue le calcul pour élire un candidat selon la méthode de vote uninominal à un ou deux tours.


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

3. Options d'Affichage : 
L'application propose une option pour afficher les calculs intermédiaires dans un fichier log.


## Utilisation

Pour exécuter le programme, utilisez la commande suivante :

```bash
bin/uninominales -i <filename.csv> -m {uni1, uni2, all} [-o <log_file>]
```

*Paramètres :*

-i : Spécifie le nom du fichier où se trouvent les données de vote.


-m : Sélectionne la méthode de vote (uni1, uni2, all).

-o : Optionnel. Spécifie le fichier log pour afficher les calculs intermédiaires.


## Exemple d'Utilisation 

```bash
bin/uninominales -i donnees_votes.csv -m uni2 -o log.txt
```

Cette commande lance le programme avec le fichier CSV "donnees_votes.csv", utilise la méthode de vote uninominal à deux tours, et écrit les calculs dans le fichier log "log.txt".


## Compilation

Pour compiler le programme, exécutez la commande suivante :

```bash
make
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
