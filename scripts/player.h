#ifndef PLAYER_H
#define PLAYER_H

class Room;

/**
 * Player class - Represents the game player
 * Manages player state and movement between rooms
 */
class Player {
private:
    bool hasKey;        // Has collected the key
    bool hasSword;      // Has collected the sword
    bool hasPrincess;   // Has rescued the princess
    Room* currentRoom;  // Current room location
    bool isAlive;       // Player's alive status

public:
    Player();  // Initialize new player
    
    // Room interaction methods
    void setCurrentRoom(Room* room);  // Move to new room
    void move();                      // Process player movement
    
    // Item collection methods
    void pickUpKey();     // Collect key
    void pickUpSword();   // Collect sword
    void savePrincess();  // Rescue princess
    
    // State check methods
    bool hasTheKey() const;      // Check if has key
    bool hasTheSword() const;    // Check if has sword
    bool hasThePrincess() const; // Check if rescued princess
    bool playerIsAlive() const;  // Check if alive
    
    Room* getCurrentRoom() const;
    void setIsAlive(bool isAlive);
};

#endif
