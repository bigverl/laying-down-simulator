#include "Room.h"

// Return room id
int Room::getID() const
{
    return id;
}

// Returns room name
std::string Room::getName() const
{
    return name;
}

// TODO: returns name of prop given its id (for use in player commands)
std::string Room::findPropName(const int &propID)
{
    return "";
}

// TODO: returns full list of room's props (ids)
std::vector<int> *Room::getProps() const
{
    return nullptr;
}

// TODO: returns directions that player can move. will determine this by referencing adjacency matrix
std::vector<int> *Room::getAdjacentCells() const
{
    return nullptr;
}

// TODO: returns room description
std::string Room::getDescription() const
{
    return "";
}

// TODO: returns room pic in ascii
std::string Room::getPic() const
{
    return "";
}
