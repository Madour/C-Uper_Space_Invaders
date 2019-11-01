# C-uper Space Invaders :rocket: 


### Plateforms

#### Linux et MacOS
Il suffit d'installer les dépendances pour pouvoir compiler.

#### Windows
Pour compiler sur windows, il vous faudra :
- Un environnement Unix (via Cygwin par exemple)
- Installer les dépendances
- Démarrer un serveur X (XWin Server, installé automatiquement avec Cygwin) avant d'executer le programme compilé

---

### Dependencies
- X11
- SDL_mixer

### Compilation
Se placer à la racine du répertoire et lancer la commande `make`

Si tout se passe bien, un executable "space" sera genéré


### Execution
Ouvrez un terminal à la racine du répertoire et lancez la commande `./space`

Si vous voulez jouer au niveau 4 par exemple, lancez la commande `./space 4`

Une surprise vous attend à la fin du jeu si vous arrivez à vaincre la Final Wave ;)

### Troubleshooting

- Si le compilateur ne trouve pas les librairies :
	1. ouvrir le fichier src/makefile
	2. modifier la variable LIBS_PATH en ajoutant le chemin vers les lib (ne pas oublier `-L`)

- Si make vous renvoie l'erreur "Clock skew detected":
	1. lancez la commande `make clean`
	2. lancez la commande `find src -exec touch \{\} \;`
	3. recompilez avec la commande `make`
---

### Todo

- [x] Implement 2 players
- [ ] Add a main menu
- [ ] Add power ups
