#include "player.h"
#include "room.h"
#include <iostream>

using std::cout;

Player::Player() : hasKey(false), hasSword(false), hasPrincess(false), 
                  currentRoom(nullptr), isAlive(true) {}

void Player::setCurrentRoom(Room *room)
{
    currentRoom = room;
    if (currentRoom)
    {
        isAlive = currentRoom->onEnter(this);
        if (currentRoom->hasKeyAvailable())
        {
            pickUpKey();
            currentRoom->keyTakenAway();
        }
        if (currentRoom->hasSwordAvailable())
        {
            pickUpSword();
            currentRoom->swordTakenAway();
        }
        if (currentRoom->hasPrincessAvailable())
        {
            savePrincess();
            currentRoom->princessTakenAway();
        }
    }
    else
    {
        std::cout << "Not a room!" << std::endl;
    }
}

void Player::pickUpKey() { hasKey = true; }
void Player::pickUpSword() { hasSword = true; }
void Player::savePrincess() { hasPrincess = true; }
void Player::setIsAlive(bool isAlive) { this->isAlive = isAlive; cout << this->isAlive; }

bool Player::hasTheKey() const { return hasKey; }
bool Player::hasTheSword() const { return hasSword; }
bool Player::hasThePrincess() const { return hasPrincess; }
bool Player::playerIsAlive() const { return isAlive; }

Room* Player::getCurrentRoom() const { return currentRoom; }

void Player::move()
{
    if (!isAlive) return;
    
    Room* nextRoom = currentRoom->chooseExit();
    if (nextRoom)
    {
        setCurrentRoom(nextRoom);
    }
    else
    {   
        std::cout << std::endl;
        std::cout << "Oops, Blocked!" << std::endl;
        std::cout << std::endl;
    }
}

