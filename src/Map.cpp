#include "Map.h"

#include <iostream>


Map &Map::getInstance()
{
    std::cout << "Map made lol";
    static Map instance;
    return instance;
}

// TODO returns id of room player currently occupies
int getPlayerPosition()
{
    return 0;
}

// returns id's of rooms adjacent to this one
std::vector<int> *getAdjacentRooms(const int &id)
{
    return nullptr;
}