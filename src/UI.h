#ifndef UI_H
#define UI_H

#include <string>

/*****************************************************************************************************
 * The 'UI' class governs printing output to screen. Follows singleton pattern. See Database class
 * for more info
 ******************************************************************************************************/
class UI
{
    // Attributes
    std::string titleScreen;
    static UI instance;

    // Methods
public:
    static UI getInstance()
    {
        return instance;
    }

    // prints room description given a room's ID
    void printRoomDescription(const int &id)
    {
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

private:
    UI() {} // private constructor
};

#endif
