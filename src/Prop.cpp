#include "Prop.h"

// Returns prop's ID
int Prop::getID() const
{
    return id;
}

// Returns prop's name
std::string Prop::getName() const
{
    return name;
}

// Returns true if item has been picked up
bool Prop::isPickedUp() const
{
    return pickedUp;
}

// Returns true if item is in its original room
bool Prop::inHomeRoom() const
{
    return homeRoom;
}

// Returns ID room where this item needs to be used
int Prop::getSolutionRoomID() const
{
    return solutionRoom;
}

// Returns prop's description when player enters "LOOK <target>"
std::string Prop::getDescription() const
{
    return description;
}

// Returns all valid commands for prop
std::vector<int> *Prop::getValidCommands() const
{
    return validCommands;
}

// Expires item after it has been used fully, and cannot be used again
void Prop::expire()
{
    expired = true;
}