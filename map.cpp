#include "map.h"
#include <random>
#include <algorithm>

Map::Map(int size) : size(size) {
    rooms.resize(size, std::vector<Room*>(size, nullptr));
    generateRooms();
    allocateSpecialRooms();
    setStartRoom();
    connectRooms();
}

Map::~Map() {
    for(auto& row : rooms) {
        for(auto& room : row) {
            delete room;
        }
    }
}

bool Map::isValidPosition(int x, int y) const {
    return x >= 0 && x < size && y >= 0 && y < size;
}

int Map::randomNumber(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void Map::dfs(int x, int y, std::vector<std::vector<bool>>& visited) {
    visited[x][y] = true;
    
    const std::pair<int, int> directions[] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    const std::string dirNames[] = {"east", "south", "west", "north"};
    
    for(int i = 0; i < 4; i++) {
        int newX = x + directions[i].first;
        int newY = y + directions[i].second;
        
        if(isValidPosition(newX, newY) && !visited[newX][newY]) {
            Room* currentRoom = rooms[x][y];
            if(currentRoom->getExit(dirNames[i]) != nullptr) {
                dfs(newX, newY, visited);
            }
        }
    }
}

bool Map::isConnected() {
    std::vector<std::vector<bool>> visited(size, std::vector<bool>(size, false));
    dfs(startRoomCoordinates.first, startRoomCoordinates.second, visited);
    
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(!visited[i][j]) return false;
        }
    }
    return true;
}

void Map::clearAllConnections() {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            rooms[i][j]->clearExits();
        }
    }
}

void Map::generateRooms() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (rooms[i][j] == nullptr) {
                rooms[i][j] = new Room();
            }
        }
    }
}

void Map::allocateSpecialRooms() {
    int keyRoomX = randomNumber(0, size - 1);
    int keyRoomY = randomNumber(0, size - 1);
    delete rooms[keyRoomX][keyRoomY];
    rooms[keyRoomX][keyRoomY] = new KeyRoom();

    int monsterRoomX = randomNumber(0, size - 1);
    int monsterRoomY = randomNumber(0, size - 1);
    while (monsterRoomX == keyRoomX && monsterRoomY == keyRoomY) {
        monsterRoomX = randomNumber(0, size - 1);
        monsterRoomY = randomNumber(0, size - 1);
    }
    delete rooms[monsterRoomX][monsterRoomY];
    rooms[monsterRoomX][monsterRoomY] = new MonsterRoom();

    int princessRoomX = randomNumber(0, size - 1);
    int princessRoomY = randomNumber(0, size - 1);
    while ((princessRoomX == keyRoomX && princessRoomY == keyRoomY) || 
           (princessRoomX == monsterRoomX && princessRoomY == monsterRoomY)) {
        princessRoomX = randomNumber(0, size - 1);
        princessRoomY = randomNumber(0, size - 1);
    }
    delete rooms[princessRoomX][princessRoomY];
    rooms[princessRoomX][princessRoomY] = new PrincessRoom();

    int swordRoomX = randomNumber(0, size - 1);
    int swordRoomY = randomNumber(0, size - 1);
    while ((swordRoomX == keyRoomX && swordRoomY == keyRoomY) || 
           (swordRoomX == monsterRoomX && swordRoomY == monsterRoomY) || 
           (swordRoomX == princessRoomX && swordRoomY == princessRoomY)) {
        swordRoomX = randomNumber(0, size - 1);
        swordRoomY = randomNumber(0, size - 1);
    }
    delete rooms[swordRoomX][swordRoomY];
    rooms[swordRoomX][swordRoomY] = new SwordRoom();

    int exitRoomX = randomNumber(0, size - 1);
    int exitRoomY = randomNumber(0, size - 1);
    while ((exitRoomX == keyRoomX && exitRoomY == keyRoomY) || 
           (exitRoomX == monsterRoomX && exitRoomY == monsterRoomY) || 
           (exitRoomX == princessRoomX && exitRoomY == princessRoomY) || 
           (exitRoomX == swordRoomX && exitRoomY == swordRoomY)) {
        exitRoomX = randomNumber(0, size - 1);
        exitRoomY = randomNumber(0, size - 1);
    }
    delete rooms[exitRoomX][exitRoomY];
    rooms[exitRoomX][exitRoomY] = new ExitRoom();
}

void Map::setStartRoom() {
    int startRoomX = randomNumber(0, size - 1);
    int startRoomY = randomNumber(0, size - 1);
    while (rooms[startRoomX][startRoomY]->isExitRoom() ||
           rooms[startRoomX][startRoomY]->hasMonsterAvailable() ||
           rooms[startRoomX][startRoomY]->hasPrincessAvailable() ||
           rooms[startRoomX][startRoomY]->hasSwordAvailable()) {
        startRoomX = randomNumber(0, size - 1);
        startRoomY = randomNumber(0, size - 1);
    }
    this->startRoomCoordinates = {startRoomX, startRoomY};
}

Room* Map::getStartRoom() {
    return rooms[startRoomCoordinates.first][startRoomCoordinates.second];
}

void Map::connectRooms() {
    do {
        clearAllConnections();
        
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                if(j < size-1 && randomNumber(0, 1)) {
                    rooms[i][j]->setExits("east", rooms[i][j+1]);
                    rooms[i][j+1]->setExits("west", rooms[i][j]);
                }
                
                if(i < size-1 && randomNumber(0, 1)) {
                    rooms[i][j]->setExits("south", rooms[i+1][j]);
                    rooms[i+1][j]->setExits("north", rooms[i][j]);
                }
            }
        }
        
        bool hasAnyConnection = false;
        for(int i = 0; i < size && !hasAnyConnection; i++) {
            for(int j = 0; j < size; j++) {
                if(!rooms[i][j]->getExits().empty()) {
                    hasAnyConnection = true;
                    break;
                }
            }
        }
        
        if(!hasAnyConnection) continue; 
        
    } while(!isConnected()); 
}
