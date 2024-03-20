# Scoreboard 3
An ESP32 driven scoreboard, made of 3 daisy-chained 8x32 MAX7219 matrices.

The 3 matrices will show:
* left-hand matrix: home team abbreviation and score; e.g.: `MNU | 3`
* central matrix: the current time (HH:MM), while the game is not active and the timer, while the game is active (MM:SS)
* right-hand matrix: the away team abbreviation and score; e.g.: `2 | MNC`
For a result similar to this:
```
MNU | 3    09:53    2 | MNC
```
