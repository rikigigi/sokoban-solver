# Sokoban solver

See [Wikipedia](https://en.wikipedia.org/wiki/Sokoban) for a description of the game.
To compile:
```
mkdir build
cd build
cmake ../
make
```
To run:
```
./boxbomb < ../level11
```

## input file example
```
8 8
1 0 0   1 0 0   1 0 0   1 0 0    1 0 0   1 0 0   1 0 0   1 0 0
1 0 0   1 0 0   0 0 0   0 0 0    0 0 0   1 0 0   1 0 0   1 0 0
1 0 0   1 0 0   0 0 0   1 0 0    0 0 1   0 0 0   0 0 0   1 0 0
1 0 0   0 0 0   0 1 1   0 1 0    0 0 0   0 1 0   0 0 0   1 0 0
1 0 0   0 0 0   0 0 0   0 0 1    0 0 1   0 0 0   1 0 0   1 0 0
1 0 0   1 0 0   1 0 0   0 0 0    1 0 0   0 1 0   1 0 0   1 0 0
1 0 0   1 0 0   1 0 0   0 0 0    0 0 0   0 0 0   1 0 0   1 0 0
1 0 0   1 0 0   1 0 0   1 0 0    1 0 0   1 0 0   1 0 0   1 0 0
3 1

```
The first two numbers are the size of the 2d grid. Then a list of triplets of 1/0 (true/false) builds the game to solve.
For each triplet, the first is 1 if the cell is a wall, the second is 1 if the cell contains a target, the third is 1 if the cell contains a box.
After this list there is the starting position (0 0 is the top right corner). Example output:
```
# # # # # # # # 
# #   %   # # # 
# #   # o     # 
#   O x   x   # 
#     o o   # # 
# # #   # x # # 
# # #       # # 
# # # # # # # #
```
With the following meaning:
 - `%` cell with the player
 - `X` cell with both the player and a target
 - `x` cell with a target
 - `#` wall
 - `o` cell with an empty box
 - `O` cell with a box on a target
 - ` ` empty cell
