#include "Prop.h"

// Returns prop's ID
int Prop::getID() const
{
    return _id;
}

// Returns prop's name
std::string Prop::getName() const
{
    return _name;
}

// Returns true if item has been picked up
bool Prop::isPickedUp() const
{
    return _pickedUp;
}

// Returns true if item is in its original room
bool Prop::inHomeRoom() const
{
    return _homeRoom;
}

// Returns ID room where this item needs to be used
int Prop::getSolutionRoomID() const
{
    return _solutionRoom;
}

// Returns prop's description when player enters "LOOK <target>"
std::string Prop::getLookDescription() const
{
    return _lookDescription;
}

// Returns all valid commands for prop
std::vector<int> *Prop::getValidCommands() const
{
    return _validCommands;
}

// Returns true if prop is expired
bool Prop::isExpired() const
{
    return _expired;
};

// Expires item after it has been used fully, and cannot be used again
void Prop::expire()
{
    _expired = true;
}

// Returns ID of room this prop is blocking
int Prop::getBlockingRoom() const
{
    return _blockingRoom;
}

// Returns text this prop should display when it blocks player
std::string Prop::getBlockerText() const
{
    return _blockerText;
}

// Print for debug
void Prop::print()
{
    std::cout << "ID: " << _id << std::endl
              << "NAME: " << _name << std::endl
              << "PICKED UP: " << _pickedUp << std::endl
              << "HOME ROOM: " << _homeRoom << std::endl
              << "SOLUTION ROOM: " << _solutionRoom << std::endl
              << "SOLUTION PROP: " << _solutionProp << std::endl
              << "BLOCKING ROOM: " << _blockingRoom << std::endl
              << "BLOCKING PROP: " << _blockingProp << std::endl
              << "VALID COMMANDS: ";

    for (unsigned int index = 0; index < _validCommands->size(); index++)
    {
        std::cout << _validCommands->at(index) << " ";
    }

    std::cout << "\n";
    std::cout << "LOOK DESCRIPTION: " << _lookDescription << std::endl
              << "USE DESCRIPTION: " << _useDescription << std::endl
              << "BLOCKER TEXT: " << _blockerText << std::endl
              << "SUCCESS TEXT: " << _successText << std::endl
              << "TALK TEXT: " << _talkText << std::endl
              << "EXPIRED: " << _expired << std::endl
              << std::endl;
}

// Full param constructor
Prop::Prop(const int &id, const std::string &name, const bool &pickedUp, const int &homeRoom, const int &solutionRoom, const int &solutionProp,
           const int &blockingRoom, const int &blockingProp, std::vector<int> *validCommands, const std::string &lookDescription,
           const std::string &useDescription, const std::string &blockerText, const std::string &successText, const std::string &talkText)
{
    _id = id;
    _name = name;
    _pickedUp = pickedUp;
    _homeRoom = homeRoom;
    _solutionRoom = solutionRoom;
    _solutionProp = solutionProp;
    _blockingRoom = blockingRoom;
    _blockingProp = blockingProp;
    _validCommands = validCommands;
    _lookDescription = lookDescription;
    _useDescription = useDescription;
    _blockerText = blockerText;
    _successText = successText;
    _talkText = talkText;
}