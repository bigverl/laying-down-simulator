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
void UserInterface::printRoomDescription(const int &id)
{
    // This is just how you'd likely get the room object. Gotta do the rest
    DB.getRoom(id);
}

// prints the available navigation directions derived from room's id
// compared to adj list
void UserInterface::printNavigation(const int &id)
{
}

// prints player inventory, probably also says 'press enter to continue'
// then reprints current room
void UserInterface::printPlayerInventory()
{
}

// prints title screen
void UserInterface::printTitleScreen()
{
}

// prints available commands
void UserInterface::printCommands() {}

// prints main menu
void UserInterface::printMainMenu()
{
    std::cout << "This is the main menu placeholder.\n"
              << "S: Start Game \n"
              << "H: Open Help Screen \n"
              << "Q: Quit Game \n\n";
}

void UserInterface::printHelp()
{
    CLEAR_SCREEN;

    // Placeholder start
    std::cout << "This is a placeholder for HELP MENU\n";
    // Placeholder end

    std::cout << "Press <ENTER> to continue";
    std::cin.ignore(); // Pause for <enter>
    CLEAR_SCREEN;
}