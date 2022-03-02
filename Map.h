#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Room.h"

/********************************************************************************************
 * The 'Map' class contains all attributes and methods required to manage the map itself.
 * Follows singleton pattern. See database class for more info
 ********************************************************************************************/
class Map
{
    // Attributes
    std::vector<int> rooms; // reference table for rooms 0 to * based on their ID's(?).
    int playerPosition;     // id of current room player occupies. will change during movement

    // TODO CONFIGURE THIS. IT WILL BE DIFFICULT
    int adjMatrix[0][0]; // 2d array of size nxn where n is the number of rooms in game. represents room adjacency.
                         // 0 for 'not connected'. 1 for 'connected'. prob needs to be dynamic glhf

    static Map instance;
    // Methods

public:
    static Map getInstance(const std::vector<Room> rooms)
    {
        return instance;
    }

    // returns id of room player currently occupies
    int getPlayerPosition()
    {
        return 0;
    }

    // returns id's of rooms adjacent to this one
    std::vector<int> *getAdjacentRooms(const int &id)
    {
        return nullptr;
    }

private:
    Map(std::vector<Room>) {} // private constructor uses data from database to populate adjMatrix
};

#endif // MAP.H