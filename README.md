<a href="https://www.buymeacoffee.com/michalsara" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-red.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>

# Mikesh's Game of Life

This is a simple implementation of Conway's Game of Life written in C++.

![screenshot](https://raw.githubusercontent.com/MikeshCZ/Game-of-Life/main/screenshot.png)

## Overview

[Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves.

## Features

- Simple graphical representation of the game board.
- Configurable board size and colors.
- Step through generations manually or automatically.

## Requirements

- C++17 or later.
- [raylib library](https://www.raylib.com/) (A simple and easy-to-use library to enjoy videogames programming).
- [raygui](https://github.com/raysan5/raygui) is a simple and easy-to-use immediate-mode-gui library (already part of `ext` folder).

## Credits

Inspired by Programming With Nick and his tutorial [Conway's Game of Life tutorial in C++ & raylib - OOP](https://youtu.be/daFYGrXq0aw?si=TnnAfXES8tl2I8s9). 

The tutorial repository is [here](https://github.com/educ8s/CPP-Game-Of-Life-with-raylib).

Thank you.

## Controls

`F1` - Show/Close this help

`Left Click` - Add cell state (alive)

`Right Click` - Remove cell state (dead)

`Space` - Start/stop the simulation

`ENTER` - Clear / Reset the board

`Key up` - Increase the simulation speed

`Key down` - Decrease the simulation speed

`Key left` - Increase cell edges

`Key right` - Decrease cell edges

`S` - Only one generation (when the game is paused)

`F` - Toggle fullscreen ON/OFF

`C` - Turn on/off random colors

`M` - Music on/off

`F10` - Exit the game

## Config file

Some of the start-up parameters can be adjusted in the `config.ini` file. If the file does not exist, it will be created during the first launch of the game with default parameters.

# Enjoy the Game of Life!

## If you like this repository you can **[buy me a coffee](https://www.buymeacoffee.com/michalsara)**. Thank You!
