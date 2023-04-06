# Game-of-Life
This is a 2D implementation of Life, a cellular automata game introducted by John Conway in 1970.

## Rules
Every cell in the grid is surrounded by eight neighbors. For every generation:

- Cells live if two or three neighbors are alive;
- Cells die if live neighbors are less than two (exposure) or more than three (overcrowding);
- Dead cells come to life if exactly three neighbors are alive.
