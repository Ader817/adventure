#include <iostream>
#include "player.h"
#include "room.h"
#include "map.h"

#define MAP_SIZE 4

int main() {

    std::cout << "Welcome to the castle adventure game!" << std::endl;
    std::cout << "Your mission is to rescue the princess and then leave the castle with the key!" << std::endl;
    std::cout << "Available command: east, west, north, south." << std::endl;

    Player player;
    Map map(MAP_SIZE);
    Room* startRoom = map.getStartRoom();
    player.setCurrentRoom(startRoom);
    while (player.playerIsAlive()) {
        player.move();
    }

    return 0;
}