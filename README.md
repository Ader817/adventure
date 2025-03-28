# Castle Adventure Game

A console-based text adventure game where players must find the princess and key to escape the castle.

## Game Objectives

- Find and rescue the princess
- Obtain the key
- Find the sword to fight monsters
- Successfully escape the castle

## Features

- Randomly generated 4x4 map
- Special rooms including:
  - Princess Room
  - Key Room
  - Sword Room
  - Monster Room
  - Exit Room
- Random room connections
- Guaranteed map connectivity

## Controls

Use the following commands to move between rooms:
- `north` - Move northward
- `south` - Move southward
- `east` - Move eastward
- `west` - Move westward

## Build and Run

### Requirements
- C++11 or higher
- Make utility

### Building Steps
```bash
# Change to build directory
cd build

# Compile the game
make

# Return to main directory
cd ..

# Run the game
./adventure

# Clean build files (from build directory)
cd build
make clean

# Rebuild
make rebuild
```

## Project Structure

```
adventure/
├── scripts/        # Source code directory
│   ├── main.cpp    # Program entry point
│   ├── player.h    # Player class declaration
│   ├── player.cpp  # Player class implementation
│   ├── room.h      # Room class declaration
│   ├── room.cpp    # Room class implementation
│   ├── map.h       # Map class declaration
│   └── map.cpp     # Map class implementation
├── build/          # Build directory
│   └── Makefile    # Build script
└── README.md       # Project documentation
```

## Game Rules

1. Player starts in a random room
2. Must find the sword before encountering monsters
3. Meeting a monster without a sword results in game over
4. Must rescue the princess and have the key to escape
5. Successfully escaping the castle wins the game

## Game Flow

1. Move through rooms using directional commands
2. Collect items (sword, key) and rescue the princess
3. Avoid or defeat monsters
4. Find the exit and escape

## End Conditions
- Victory: Escape the castle with both princess and key
- Defeat: Get eaten by a monster

## Note

- Map is randomly generated each game
- All rooms are guaranteed to be reachable
- Game ends when either:
  - Player is defeated by monster
  - Player successfully escapes
