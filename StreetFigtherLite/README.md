# Street Figther Lite

Ce projet est une reprise du jeu Street Fighter II codé en C++ et utilisant la librairie SFML. Il dispose d'un mode d'affichage en version texte et d'un mode en version graphique (SFML).

# Guide de démarrage

Ce projet dispose d'un Makefile lui permettant de compiler dans un terminal ou en utilisant CodeBlocks (disponible sur Windows, Linux et MacOS).

## Prérequis

### Pour une compilation et une exécution dans le terminal (uniquement sous Linux et MacOS)

Vous devez installer la librairie SFML.

#### MacOS
```
$ brew install sfml
```
#### Linux
```
$ sudo apt-get install libsfml-dev
```


### Pour une compilation et une exécution avec CodeBlocks (Windows, Linux et MacOS)

Vous devez installer l'IDE CodeBlocks et le compilateur MinGW Builds 7.3.0.

Télécharger [CodeBlocks](http://www.codeblocks.org/downloads/26)

Télécharger [MinGW 7.3.0](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/i686-7.3.0-release-posix-dwarf-rt_v5-rev0.7z/download)

#### IMPORTANT : Sous Windows la version du compilateur doit correspondre exactement à la 7.3.0.


## Compilation et execution

### Dans le terminal

Il faut se mettre à la racine du répertoire du projet et lancer la commande : 

```
$ make
```

Une fois la compilation effectué, vous pouvez lancer le jeu en mode texte avec la commande : 

```
$ ./bin/executable_txt
```

Et en mode graphique avec la commande : 

```
$ ./bin/executable_sfml
```


### Dans CodeBlocks

- Après avoir installer CodeBlocks et le compilateur, double-cliquez sur *StreetFigtherLite.cbp* se trouvant à la racine du répertoire.
- Selectionner la cible de compilation, soit **SF_Graphic** soit **SF_Txt** dans le menu déroulant *Build Target*. 
- Cliquer sur *Build and Run*, pour compiler et lancer le mode choisit.

#### Remarque : Sous Windows, après compilation le projet peut être exécuté directement en lançant les fichiers executable_sfml.exe / executable_txt.exe se trouvant dans le répertoire bin.


# Lancer les tests de regression

### Dans le terminal

Après avoir compiler le projet, à la racine du répertoire du projet lancer la commande : 

```
$ ./bin/testregression
```

# Génération de la documentation

Il faut se mettre à la racine du répertoire du projet et lancer la commande : 

```
$ doxygen doc/doxyfile
```

Puis ouvrir le fichier index.html se trouvant dans doc/html.

# Réalisé avec 

* [Sublime Text 3](https://www.sublimetext.com/docs/3/) - L'éditeur utilisé
* [CodeBlocks](http://wiki.codeblocks.org/index.php/User_documentation) - L'IDE utilisé
* [SFML 2.5.1](https://www.sfml-dev.org/documentation/2.5.1/) - Le module graphique utilisé


# Auteurs

* **Adam ALLOMBERT-GOGET p1807279**
* **Nicolas CHAMAND p1908794**
* **Ilyes KORICHI p1810510** 

# Copyright et License

Toutes les textures de ce projet sont la propriété de CAPCOM.
Copyright © CAPCOM, INC. ALL RIGHTS RESERVED.

# Remerciements

Remerciement à M. Nicolas PRONOST, notre encadrant de projet LIFAP4, pour son aide précieuse dans la réalisation de ce projet. 
