# Nom du robot autonome

## Sommaire
	 1. Introduction
	 2. Objectif de ce projet
	 3. Installation
	 4. Documentation

## Introduction
Projet de synthèse de Master 1 IISC de l'Univrsité de Cergy-Pontoise de Filipe GAMA, Remy GIRARD, Bruno TESSIER et Paul VALENTIN.
Ces algorithmes seront implémentés sur un robot de type aspirateur (Roomba ou ...) qui sera équipé d'une caméra.

## Objectif de ce projet
L'objectif de ce projet est de faire en sorte qu'un robot puisse se mouvoir dans une pièce de façon autonome jusqu'à un, ou plusieurs objectifs.

## Installation

### Build
Créer un dossier "build" à la racine du dossier, et se placer dans celui-ci.
Utiliser la commande "cmake ../"" (si la commande n'est pas installée, utiliser "apt-get install cmake")
Utiliser la commande "make"
Lancer le programme avec ./hello

### Tests
Les tests sont contenus dans le dossier "tests/".
Une fois dans ce dossier, utiliser la commande "make"
Lancer le programme "./tests.out"
Pour supprimer les fichiers créés, faire "make clean" et "make clean_Logs"

## Documentation
