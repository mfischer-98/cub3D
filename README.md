*This project has been created as part of the 42 curriculum by mefische and ntomas-g.*

# cub3D

## Description
cub3D is a small 3D game engine inspired by Wolfenstein 3D, built in C with MiniLibX as part of the 42 curriculum. The project renders a first-person view from a 2D map using raycasting and DDA, then projects textured wall slices to the screen to create the illusion of a 3D environment.

In our version, the player explores a haunted hotel with textured walls, directional wall rendering, collision handling and fog effect for atmosphere.

## Features
- Raycasting-based first-person rendering using DDA grid stepping.
- Textured wall rendering with directional wall selection: north, south, east and west.
- Player movement with rotation, forward/backward motion and strafing.
- Collision detection against walls.
- Perpendicular distance correction to avoid fisheye distortion.
- Fog support for better atmosphere.
- Parsing and validation of `.cub` maps and assets.

## Instructions

### Clone the repository
```bash
git clone git@github.com:mfischer-98/cub3D.git
cd cub3D
```

### Requirements
To build and run the project on Linux, you need:
- `gcc`
- `make`
- X11 headers and libraries

If these are not installed, use:

```bash
sudo apt-get update
sudo apt-get install -y gcc make xorg libxext-dev libbsd-dev libx11-dev
```

MiniLibX for Linux also documents the Debian/Ubuntu package set `gcc make xorg libxext-dev libbsd-dev` as an example dependency install.

### Compilation
Clone the repository and run:

```bash
make
```

Cleanup rules:

```bash
make clean
make fclean
make mlxclean
make re
```
`make mlxclean` removes the MiniLibX repository.


### Execution
Run the program with a valid `.cub` map:

```bash
./cub3D maps/example.cub
```

### Controls
- `F` to turn fog on/off
- `W` / `S` to move forward and backward
- `A` / `D` to strafe left and right
- `Left` / `Right` arrow keys to rotate
- `ESC` to quit

## Project structure
```text
├── inc/
│   └── cub3d.h
├── inc_bonus/
│   └── cub3d_bonus.h
├── maps/
│   ├── fail/
│   └── pass/
├── src/
│   ├── parser/
│   └── *.c
├── src_bonus/
│   ├── parser_bonus/
│   └── *_bonus.c
├── libft/
├── textures/
├── Makefile
└── README.md
```

## Technical choices

### Raycasting
The renderer casts one ray per screen column. Each ray advances through the 2D grid using DDA until it hits a wall, then computes the perpendicular wall distance and converts that into the height of the wall slice drawn on screen. This is the classic raycasting approach used in early grid-based 3D engines.

### Texturing
After a wall hit is found, the engine selects the correct texture according to the wall face, computes the horizontal texture coordinate from the hit position, and samples texture pixels vertically along the projected wall slice. This creates textured walls with relatively low computational cost.

### Movement and collisions
Player movement is resolved independently on the x and y axes, which allows smoother wall sliding and avoids common collision issues in tile-based movement. Collision tests are done against the parsed 2D map to prevent entering wall cells.

### Map validation
The parser is responsible for loading the `.cub` file, normalizing the map layout, and validating that the playable area is enclosed. This is important because the renderer and movement system assume safe grid access during traversal.

## Resources
### References
- Fabien Sanglard, *Game Engine Black Book: Wolfenstein 3D*.
- Lode Vandevenne, [Raycasting](https://lodev.org/cgtutor/raycasting.html).
- YouTube, [Super Fast Ray Casting in Tiled Worlds using DDA](https://www.youtube.com/watch?v=NbSee-XM7WA).

These resources were used to understand DDA stepping, perpendicular wall distance, texture mapping and the general structure of a Wolfenstein-style rendering pipeline.

### Additional documentation
- MiniLibX Linux repository: [42Paris/minilibx-linux](https://github.com/42paris/minilibx-linux). [web:212]
