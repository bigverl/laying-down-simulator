#include "Database.h"
#include "UserInterface.h"

// Creates one instance of UserInterface. If one exists, it returns the existing one.
UserInterface &UserInterface::getInstance()
{
    static UserInterface instance;
    return instance;
}

// TODO: Prints room default description given a room's ID
// Need to figure out how to differentiate between default desc and
// alternate desc, tho
void printDescription(const int &id)
{
    // This is just how you'd likely get the room object. Gotta do the rest
    DB.getRoom(id);
}

// prints the available navigation directions derived from room's id
// compared to adj list
void printNavigation(const int &id)
{
}

// prints player inventory, probably also says 'press enter to continue'
// then reprints current room
void printPlayerInventory()
{
}

// prints title screen
void printTitleScreen()
{
}

// prints available commands
void printCommands() {}