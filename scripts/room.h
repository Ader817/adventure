#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <map>

class Player;

/**
 * Base Room class - Represents a room in the game
 * Manages room properties and connections to other rooms
 */
class Room {
protected:
    std::map<std::string, Room*> exits;  // Map of directions to connected rooms
    bool hasMonster;                      // Contains a monster
    bool hasPrincess;                     // Contains the princess
    bool hasKey;                          // Contains the key
    bool hasSword;                        // Contains the sword
    bool hasExit;                         // Is an exit room

public:
    // Constructor with room property flags
    Room(bool hasMonster = false, bool hasPrincess = false, bool hasKey = false, 
         bool hasSword = false, bool hasExit = false);
    virtual ~Room() = default;
    
    // Room interaction methods
    void setExits(std::string direction, Room* room);  // Set room connection
    virtual bool onEnter(Player* player);              // Handle player entry
    Room* getExit(std::string direction);             // Get connected room
    Room* chooseExit();                               // Process player movement choice
    
    // Property check methods
    bool hasSwordAvailable() const;
    bool hasPrincessAvailable() const;
    bool hasMonsterAvailable() const;
    bool hasKeyAvailable() const;
    bool isExitRoom() const;

    void swordTakenAway();
    void princessTakenAway();
    void keyTakenAway();

    void clearExits() { exits.clear(); }
    const std::map<std::string, Room*>& getExits() const { return exits; }
};

// Specialized room types
/**
 * KeyRoom - Contains the key needed to exit the castle
 */
class KeyRoom : public Room {
public:
    KeyRoom();
    bool onEnter(Player* player) override;
};

/**
 * MonsterRoom - Contains a monster that will end the game
 * unless the player has a sword
 */
class MonsterRoom : public Room {
public:
    MonsterRoom();
    bool onEnter(Player* player) override;
};

/**
 * PrincessRoom - Contains the princess that the player needs to rescue
 */
class PrincessRoom : public Room {
public:
    PrincessRoom();
    bool onEnter(Player* player) override;
};

/**
 * SwordRoom - Contains the sword needed to defeat the monster
 */
class SwordRoom : public Room {
public:
    SwordRoom();
    bool onEnter(Player* player) override;
};

/**
 * ExitRoom - Represents the exit of the castle
 */
class ExitRoom : public Room {
public:
    ExitRoom();
    bool onEnter(Player* player) override;
};

#endif
