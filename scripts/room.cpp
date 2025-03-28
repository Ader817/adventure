#include "room.h"
#include "player.h"
#include <iostream>

using std::string;
using std::map;
using std::cout;
using std::cin;
using std::endl;

Room::Room(bool hasMonster, bool hasPrincess, bool hasKey, bool hasSword, bool hasExit) 
    : hasMonster(hasMonster), hasPrincess(hasPrincess), hasKey(hasKey), 
      hasSword(hasSword), hasExit(hasExit) {}

KeyRoom::KeyRoom() : Room(false, false, true, false, false) {}

MonsterRoom::MonsterRoom() : Room(true, false, false, false, false) {}

PrincessRoom::PrincessRoom() : Room(false, true, false, false, false) {}

SwordRoom::SwordRoom() : Room(false, false, false, true, false) {}

ExitRoom::ExitRoom() : Room(false, false, false, false, true) {}

void Room::setExits(string direction, Room *room) {
    exits.insert({direction, room});
}

bool Room::onEnter(Player* player) {
    cout << endl;
    cout << "You have entered a room." << endl;
    return true;
}

Room* Room::getExit(string direction) {
    if(exits.find(direction) == exits.end()) {
        return nullptr;
    }
    return exits[direction];
}

Room* Room::chooseExit() {
    cout << "There are " << exits.size() << " exits: ";
    for (const auto& exit : exits) {
        cout << exit.first << " ";
    }
    cout << endl;
    cout << "Enter your command:" << endl;
    string command;
    while (true) {
        cin >> command;
        if (command == "east" || command == "west" || command == "north" || command == "south") {
            break;
        }
        cout << "Invalid command. Please try again." << endl;
    }
    return getExit(command);
}

bool Room::hasSwordAvailable() const { return hasSword; }
bool Room::hasPrincessAvailable() const { return hasPrincess; }
bool Room::hasMonsterAvailable() const { return hasMonster; }
bool Room::hasKeyAvailable() const { return hasKey; }
bool Room::isExitRoom() const { return hasExit; }

void Room::swordTakenAway() { hasSword = false; }
void Room::princessTakenAway() { hasPrincess = false; }
void Room::keyTakenAway() { hasKey = false; }

bool KeyRoom::onEnter(Player* player) {
    cout << endl;
    cout << "You have entered the key room." << endl;
    if (hasKey) {
        cout << "You found the key!" << endl;
    }
    else {
        cout << "You have already taken the key." << endl;
    }
    return true;
}

bool MonsterRoom::onEnter(Player* player) {
    cout << endl;
    cout << "You have entered the monster room." << endl;
    if (hasMonster) {
        cout << "A monster is here!" << endl;
        cout << "You need to fight it!" << endl;
        cout << endl;
        if (player->hasTheSword()) {
            cout << "You killed the monster with your sword!" << endl;
            hasMonster = false;
            return true;
        } else {
            cout << "NO!!! You don't have a sword!" << endl;
            cout << "You have been eaten by the monster." << endl;
            cout << "Game Over!" << endl;
            return false;
        }
    }
    else {
        cout << "The monster is already dead." << endl;
        return true;
    }
}

bool PrincessRoom::onEnter(Player* player) {
    cout << endl;
    cout << "You have entered the princess room." << endl;
    if (hasPrincess) { 
        cout << "You have saved the princess!" << endl;
        cout << "Now you can leave the castle." << endl;
    }
    else {
        cout << "You have already saved the princess." << endl;
    }
    return true;
}

bool SwordRoom::onEnter(Player* player) {
    cout << endl;
    cout << "You have entered the sword room." << endl;
    if (hasSword) {
        cout << "You found a sword!" << endl;
        cout << "Now you can fight against the monster." << endl;
    }
    else {
        cout << "You have already taken the sword." << endl;
    }
    return true;
}

bool ExitRoom::onEnter(Player* player) {
    cout << endl;
    cout << "You have entered the exit room." << endl;
    if (player->hasTheKey() && player->hasThePrincess()) {
        cout << "You have escaped the castle!" << endl;
        cout << "Game Over!" << endl;
        return false;
    }
    else if (player->hasThePrincess()) {
        cout << "You need the key to leave the castle." << endl;
        cout << "You have to go back and find it." << endl;
        return true;
    }
    else if (player->hasTheKey()) {
        cout << "You need to save the princess first." << endl;
        cout << "You have to go back and find her." << endl;
        return true;
    }
    else {
        cout << "You need the key and the princess to leave the castle." << endl;\
        cout << "You have to go back and find them." << endl;
        return true;
    }
}
