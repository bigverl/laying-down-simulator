#include "Map.h"

// Creates one instance of Map. If one exists, it returns the existing one.
Map &Map::getInstance()
{
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