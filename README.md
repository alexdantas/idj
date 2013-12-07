# IDJ Part 4

Two-player fast-paced space dodger game, with SDL 1.2 in C++.

Features:

* Fast-paced action! Smooth camera scroll.
* Nice parallax effects on background scenery!
* Awesome music - non licensed, so I'll probably get sued.
* Supports maps created with [Tiled][tiled]! Check out `map/map.tmx`!

![title](http://www.alexdantas.net/projects/idj-part-4/screenshots/title.png)
![game](http://www.alexdantas.net/projects/idj-part-4/screenshots/game.png)

## Usage

Everything should come out fine by simply doing:

    $ make

There's a lot of components, so it should take a while to compile.

## Requirements

Make sure you have [SDL 1.2][sdl] and it's child libs installed -
SDL TTF, SDL GFX, and such...

On a Debian-based distro, the following should do:

    $ sudo apt-get install libsdl*

Any other dependencies are included with this package, so don't
worry.

## Controls

The first player controls a lonely human space ship, searching for Earth.
It has an energy bar and should avoid coliding with any planets on it's way.

| Key        | Action           |
| :--------: | :--------------: |
| Arrow Keys | Control the ship |
| Shift      | Make sharp turns |

Meanwhile, the second player controls an alien spaceship obsessed with
destroying the first player. It can summon planets onscreen and

| Key                 | Action                                    |
| :-----------------: | :---------------------------------------: |
| Left mouse button   | Create random planets on the screen.      |
| Right mouse button  | Order ship to walk to that specific place |
| Middle mouse button | Clear path queue                          |

Other keys:

| Key                | Action                                    |
| :----------------: | :---------------------------------------: |
| ESC, q             | Quit game |
| p                  | Pause game |
| F2                 | Force Game Over |
| f                  | Toggle fullscreen mode |
| r                  | Reload settings on `config.ini` file |
| m                  | Reload map settings on `map.tmp` file |
| F1                 | Debug: Show bounding boxes of all objects |

## Development

This is a HUGE codebase - not trivial to understand in one sit.
I've tried my best to comment and describe everything, specially
on class headers.
I suggest you to begin by `src/main.cpp` and then follow on.

The Doxygen documentation might help:

    $ make dox

We have a lot of useful modules anybody can use on their games.
With minor modifications (or none at all) you can plug them in
into your projects. Check out:

* `src/Timer.hpp`
* `src/Music.hpp`
* `src/Animation.hpp`

And if you want to use SDL 1.2 into your C++ games, `src/SDL.hpp`
is a great wrap-up among most functionalities.

Huge thanks to [Lazy Foo's SDL tutorials][lazyfoo] - I've went
through all of them when making C++ wrappers.

## Author

Hello, there! I'm Alexandre Dantas and I made `idj` as an assignment for a class
on Introduction to Game Development.

As a matter of fact, `idj` means exactly that in portuguese:

* Introducao = Introduction
* Desenvolvimento = Development
* Jogos = Games

You can reach me by:

* Mail: `eu (at) alexdantas.net`
* Website: [alexdantas.net](http://alexdantas.net)

[sdl]: http://www.libsdl.org/download-1.2.php
[tiled]: http://www.mapeditor.org/
[lazyfoo]: http://lazyfoo.net/SDL_tutorials/

