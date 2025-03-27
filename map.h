#ifndef MAP_H
#define MAP_H

#include "room.h"
#include <vector>
#include <utility>

/**
 * Map class - Manages the game map and room connections
 * Handles room generation, special room allocation, and map connectivity
 */
class Map {
private:
    std::vector<std::vector<Room*>> rooms;    // 2D grid of rooms
    Room* startRoom;                          // Starting room pointer
    int size;                                 // Map size (size x size grid)
    std::pair<int, int> startRoomCoordinates; // Starting room location
    
    // Helper functions for map generation and validation
    bool isValidPosition(int x, int y) const;    // Check if coordinates are within map bounds
    void dfs(int x, int y, std::vector<std::vector<bool>>& visited); // DFS for connectivity check
    bool isConnected();                          // Check if all rooms are reachable
    void clearAllConnections();                  // Remove all room connections
    int randomNumber(int min, int max);          // Generate random number in range
    void generateRooms();                        // Initialize basic rooms
    void allocateSpecialRooms();                // Place special rooms randomly
    void setStartRoom();                         // Choose and set starting room

public:
    Map(int size);   // Constructor with map size parameter
    ~Map();          // Destructor to clean up room pointers
    void connectRooms();  // Establish connections between rooms
    Room* getStartRoom(); // Get pointer to starting room
};

#endif
