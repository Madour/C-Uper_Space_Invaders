# C-uper Space Invader #
---

#### Dépendences ####
- X11
- SDL_mixer

#### Compilation ####
Se placer à la racine du répertoire et lancer la commande `make`

Si tout se passe bien, un executable "space" sera genéré


#### Execution ####
Ouvrez un terminal à la racine du répertoire et lancez la commande `./space`

Si vous voulez jouer au niveau 4 par exemple, lancez la commande `./space 4`


#### Troubleshooting ####
- Si le compilateur ne trouve pas les librairies :
	1. ouvrir le fichier src/makefile
	2. modifier la variable LIBS_PATH en ajoutant le chemin vers les lib (ne pas oublier `-L`)

- Si make vous renvoie l'erreur "Clock skew detected":
	1. lancez la commande `make clean`
	2. lancez la commande `find src -exec touch \{\} \;`
	3. recompilez avec la commande `make`

---
##### Contributors #####
> Modar NASSER
> Paul FOURCADE (gameplay du boss)
