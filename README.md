# So Long

A 2D puzzle adventure game built in C using the MLX42 graphics library. Navigate through maze-like levels, collect treasures, and reach the exit while avoiding obstacles and enemies.

## Table of Contents

- [About](#about)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Game Rules](#game-rules)
- [Map Format](#map-format)
- [Controls](#controls)
- [Bonus Features](#bonus-features)
- [Project Structure](#project-structure)
- [Building](#building)

## About

So Long is a 2D top-down adventure game where you control a dwarf character navigating through challenging mazes. The goal is to collect all the treasures (amethyst gems) in the level and reach the exit door. The game includes collision detection, pathfinding validation, and smooth character movement.

This project is part of the 42 School curriculum and demonstrates:
- 2D graphics programming with MLX42
- Game loop implementation
- Collision detection algorithms
- Map parsing and validation
- Memory management in C

## Features

### Base Game
- **Character Movement**: Smooth WASD movement with collision detection
- **Collectible System**: Gather all amethyst gems to unlock the exit
- **Map Validation**: Ensures valid, solvable maps with proper boundaries
- **Move Counter**: Tracks the number of moves made (displayed in terminal)
- **Exit Condition**: Win by collecting all items and reaching the exit

### Bonus Features
- **Character Animation**: Animated walking sprites for the dwarf character
- **Enemy AI**: Moving goblin enemies with pathfinding
- **Enhanced UI**: On-screen move counter and score display
- **Sprite Animations**: Directional movement animations
- **Game Over Conditions**: Lose if touched by an enemy

## Prerequisites

Before building the project, ensure you have:

- **C Compiler**: GCC or Clang
- **Make**: Build automation tool
- **CMake**: Required for MLX42 library
- **OpenGL Development Libraries**:
  ```bash
  # Ubuntu/Debian
  sudo apt update
  sudo apt install build-essential cmake libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev libopengl-dev
  
  # macOS (with Homebrew)
  brew install cmake glfw
  ```

## Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/omartela/solong.git
   cd solong
   ```

2. **Build the project**:
   ```bash
   # Build base game
   make
   
   # Build bonus version
   make bonus
   
   # Clean build files
   make clean
   
   # Complete clean (removes dependencies)
   make fclean
   ```

## Usage

### Basic Game
```bash
./so_long maps/test1.ber
```

### Bonus Version
```bash
./so_long_bonus maps/testmapbonus.ber
```

### Command Line Arguments
- **map_file.ber**: Path to a valid map file in .ber format

### Example Maps
The `maps/` directory contains several example maps:
- `test1.ber` - Basic test map
- `testmap.ber` - More complex maze
- `bigmap.ber` - Large challenging map
- `testmapbonus.ber` - Map designed for bonus features

## Game Rules

1. **Objective**: Collect all collectibles (C) and reach the exit (E)
2. **Movement**: Use WASD keys to move the player (P)
3. **Walls**: Represented by '1' - cannot be passed through
4. **Empty Space**: Represented by '0' - safe to walk on
5. **Win Condition**: Collect all gems and reach the exit
6. **Bonus Loss Condition**: Avoid touching enemies (moving goblins)

## Map Format

Maps use the `.ber` file extension and must follow these rules:

### Map Characters
- `1` - Wall (impassable)
- `0` - Empty space (walkable)
- `P` - Player starting position (exactly one required)
- `C` - Collectible item (at least one required)
- `E` - Exit door (exactly one required)

### Map Requirements
- **Rectangular**: All rows must have the same length
- **Enclosed**: Must be surrounded by walls (1's)
- **Valid Path**: Must have a valid path from player to all collectibles and the exit
- **Single Player**: Exactly one player starting position
- **Single Exit**: Exactly one exit
- **Collectibles**: At least one collectible item

### Example Map
```
1111111111111111
1000000000000011
1111111111111C01
1111111111111101
11C0000000000001
1P01111111111111
1011111111111111
1C000000000000C1
1111111111111101
1111111111111C01
1E00000000000011
1111111111111111
```

## Controls

### Base Game
- `W` or `↑` - Move up
- `A` or `←` - Move left
- `S` or `↓` - Move down  
- `D` or `→` - Move right
- `ESC` - Exit game

### Bonus Version
Same controls as base game, plus:
- On-screen move counter and score display
- Animated character sprites
- Enemy movement (automatic)

## Bonus Features

The bonus version (`so_long_bonus`) includes:

### Enhanced Graphics
- **Animated Player**: Walking animation sprites for all directions
- **Directional Sprites**: Different sprites for left/right movement
- **Idle Animations**: Character idle states

### Enemy System
- **Goblin Enemies**: Autonomous moving enemies
- **AI Movement**: Enemies move randomly through the map
- **Collision Detection**: Game over if player touches an enemy
- **Enemy Animation**: Animated goblin sprites

### UI Improvements
- **On-Screen HUD**: Move counter and score displayed in the game window
- **Real-time Updates**: HUD updates immediately with game state changes

## Project Structure

```
solong/
├── Makefile              # Build configuration
├── so_long.h             # Main header file
├── main.c                # Main program entry point
├── maps/                 # Example map files
│   ├── test1.ber
│   ├── testmap.ber
│   ├── bigmap.ber
│   └── testmapbonus.ber
├── png/                  # Game sprites and textures
│   ├── DwarfSprite1.png  # Player character
│   ├── amethyst.png      # Collectible gems
│   ├── Rock Pile 1.PNG   # Wall textures
│   ├── Door02.png        # Exit door
│   └── goblin*.png       # Enemy sprites (bonus)
├── libft/                # Custom C library
├── bonus/                # Bonus version source files
│   ├── so_long_bonus.h
│   ├── main_bonus.c
│   └── *_bonus.c         # Enhanced game features
├── *.c                   # Core game source files
├── collision.c           # Collision detection
├── movement.c            # Player movement logic
├── read_map.c            # Map file parsing
├── validate_map.c        # Map validation
├── bfs.c                 # Pathfinding algorithms
└── init_game.c           # Game initialization
```

## Building

The project uses a Makefile with the following targets:

- `make` or `make all` - Build the base game
- `make bonus` - Build the bonus version
- `make clean` - Remove object files
- `make fclean` - Remove all generated files and dependencies
- `make re` - Rebuild everything from scratch

### Dependencies
The build system automatically handles:
- **libft**: Custom C library (built from source)
- **MLX42**: Graphics library (cloned and built automatically)
- **GLFW**: Graphics framework (system dependency)

## Technical Details

### Graphics
- **Library**: MLX42 (OpenGL-based graphics library)
- **Resolution**: 32x32 pixel tiles
- **Format**: PNG sprites and textures

### Algorithms
- **BFS Pathfinding**: Validates map solvability before game start
- **Collision Detection**: Pixel-perfect collision system
- **Memory Management**: Proper cleanup and error handling

### Performance
- **60 FPS**: Smooth gameplay with efficient rendering
- **Low Memory**: Optimized for minimal memory usage
- **Cross-Platform**: Works on Linux and macOS

---

**Author**: omartela  
**School**: 42 School  
**Project**: so_long  
**Language**: C  
**Graphics**: MLX42