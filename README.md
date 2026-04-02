# TP IA

Ce projet regroupe les trois exercices du TD d'IA Embarqué, en ING3 INEM

## 1- Lancement des exercices

A la racine du projet, se trouve trois fichiers :

- **launchExo1.sh**
- **launchExo2.sh**
- **launchExo3.sh**

Servant chacun à lancer un exercice, contenant l'entrainement + les tests.

## 2- Organisation des sources

**src/** contient les sources C et les Makefiles (une paire C + Makefile par exercice)

**par/** contient les fichiers de paramètres avec les chiffres **modèles** à reconnaître, ainsi que les données bruitées pour effectuer les tests

**gnuplot** contient les scripts des graphes, un script par graphique

**rapport** contient le rapport, au format .odt et .pdf

**dat/** contient les résultats des éxécutions :

- fichiers .csv avec les traces

- images .png avec les graphes gnuplot
