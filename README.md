# C-snake
## my gcc --version 11.3.0
### 1. compile snake module
```
gcc -W -g -c snake.c -lnsnake
```
### 2. compile program
```
gcc -W -g game.c -lncurses snake.o -o game
```
### 3. run 
```
./game
```
