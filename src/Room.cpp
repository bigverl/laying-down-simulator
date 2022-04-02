#include "Room.h"

// Return room id
int Room::getID() const
{
    return _id;
}

// Returns room name
std::string Room::getName() const
{
    return _name;
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

void Room::print()
{
    std::cout << std::endl
              << "ID: " << _id << std::endl
              << "NAME: " << _name << std::endl;

    std::cout << "PROPS: ";
    for (unsigned int index = 0; index < _props->size(); index++)
    {
        std::cout << _props->at(index) << " ";
    }
    std::cout << std::endl;

    std::cout << "ADJACENT ROOMS: ";
    for (unsigned int index = 0; index < _adjacentRooms->size(); index++)
    {
        std::cout << "  ADJACENT ROOM ID: " << _adjacentRooms->at(index)._roomID << " ";
        std::cout << "  ADJACENT ROOM DIRECTION: " << _adjacentRooms->at(index)._direction << " ";
    }
    std::cout << std::endl;

    std::cout << "DESCRIPTION TEXT DEFAULT: " << _descriptionTextDefault << std::endl;
    std::cout << "DESCRIPTION TEXT SOLVED: " << _descriptionTextSolved << std::endl;
    std::cout << "DESCRIPTION PIC: " << _descriptionPic << std::endl;
}

// Constructors
Room::Room(const int &id,
           const std::string &name,
           std::vector<int> *props,
           std::vector<AdjacentRoom> *adjacentRooms,
           const std::string &descriptionTextDefault,
           const std::string &descriptionTextSolved,
           const std::string &descriptionPic)
{
    _id = id;
    _name = name;
    _props = props;
    _adjacentRooms = adjacentRooms;
    _descriptionTextDefault = descriptionTextDefault;
    _descriptionTextSolved = descriptionTextSolved;
    _descriptionPic = descriptionPic;
}
