#ifndef MAP_H
#define MAP_H

#include "Room.h"
#include <vector>
#include <iostream>

// This is a macro. You refer to the Map instance as this name when programming
#define MAP (Map::getInstance())

/********************************************************************************************
 * The 'Map' class contains all attributes and methods required to manage the map itself.
 * Follows singleton pattern. See database class for more info
 ********************************************************************************************/
class Map
{
    // Attributes
    std::vector<int> rooms; // reference table for rooms 0 to * based on their ID's(?).
    int playerPosition;     // id of current room player occupies. will change during movement

    // Methods
    Map() = default; // private constructor

public:
    // Creates one instance of database. If one exists, it returns the existing one.
    static Map &getInstance();

    // Returns ID of room player currently occupies
    int getPlayerPosition();

    // Returns id's and directions of rooms adjacent given room ID
    std::vector<int> *getAdjacentRooms(const int &id);

private:
    Map(std::vector<Room>) {} // private constructor uses data from database to populate adjMatrix
};

#endif // MAP.H
