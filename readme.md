# C-uper Space Invaders :rocket: 

#### A remake of the classic arcade game written in C language.
##### Controls:
* Player 1:
    * Left and right arrows to move
    * Up arrow/Space bar to shoot
* Player 2:
    * Left Control to join
    * S and G to move
    * E to shoot

---
### Platforms

#### Linux et MacOS
Install dependencies and you should be able to compile and run.

#### Windows
To compile for windows, you'll need :
- A Unix like environment  (via Cygwin for example)
- Install dependencies
- Start a X server (XWin Server, installed with cygwin automatically) before running the game

---

### Dependencies
- X11
- SDL_mixer

### Compilation
Open terminal in project root and run `make`

If evverything goes well, you'll get a executable file called "space" 


### Execution
Open a terminal in project root and run `./space`

If you want to start game at wave 4 for example, just run `./space 4`

Keep playing until the Final Wave, there's a surprise at the end ;)

### Troubleshooting

- If gcc is unable to find the libs :
	1. open src/makefile
	2. add  `/path/to/libs` to LIBS_PATH variable (don't forget `-L`)

- If make command returns a "Clock skew detected" error:
	1. run `make clean`
	2. then `find src -exec touch \{\} \;`
	3. and re-compile again with `make`
---

### Todo

- [x] Implement 2 players
- [ ] Add a main menu
- [ ] Add story !
- [ ] Add power ups
