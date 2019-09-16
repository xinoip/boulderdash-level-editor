# Boulderdash Level Maker

This is a level maker/editor program for my boulderdash clone (in C).

## Main Game

Main game that i made is [here](https://github.com/xinoip/boulderDash).

### What it does?

It works as a basic tilemap editor. Select tiles and paint.
For camera movement, use arrow keys.

## Command Line Arguments

You need to pass 6 arguments when running the program.
The arguments are, levels
1. Name
2. Timelimit
3. Required diamonds to open door
4. Canvas row limit
5. Canvas col limit
6. Water spread speed (ms)

```bash
./app MyLevel 150 30 128 56 3000
```

## Produced File

Produced file will be a basic txt file, and it will work for my game.

You can change the symbols of tiles in [base.h](https://github.com/xinoip/bd-level-editor/blob/master/base.h) file.
