#ifndef UI_H
#define UI_H

#include <string>
#include "Player.h"

// This is a macro. You refer to the UserInterface instance as this name when programming
#define UI (UserInterface::getInstance())
#define CLEAR_SCREEN (std::cout << "\033[2J\033[1;1H")

/*****************************************************************************************************
 * The 'UI' class governs printing output to screen. Follows singleton pattern. See Database class
 * for more info
 ******************************************************************************************************/
class UserInterface
{
    // Attributes
    std::string titleScreen;
    // Methods
    UserInterface() = default; // private constructor

public:
    // Creates one instance of database. If one exists, it returns the existing one.
    static UserInterface &getInstance();

    // prints room description given a room's ID
    void printRoomDescription(const int &id);

    // prints the available navigation directions derived from room's id
    // compared to adj list
    void printNavigation(const int &id);

    // Prints player inventory, probably also says 'press enter to continue'
    // then reprints current room
    void printInventoryScreen();

    //
    void printPlayerInventory();

    // prints title screen
    void printTitleScreen();

    // prints available commands
    void printCommands();

    // prints main menu
    void printMainMenu();

    void printHelp();
};

#endif
