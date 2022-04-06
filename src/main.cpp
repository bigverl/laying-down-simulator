#include "Database.h"
#include "Map.h"
#include "Player.h"
#include "Prop.h"
#include "Room.h"
#include "UserInterface.h"
#include <iostream>

int main(int argc, char *argv[])
{

    /**************************************************************************
     * Declaration
     **************************************************************************/

    // Enum outlining actions player can take
    enum Actions
    {
        USE,
        LOOK,
        GET,
        PUSH,
        PULL,
        TALK,
        OPEN,
        CLOSE,
        HELP,
        QUIT,
        INVENTORY
    };

    // Enum outlining directions players may move
    enum Directions
    {
        NORTH,
        WEST,
        SOUTH,
        EAST,
    };

    // Enum representing command structure
    enum Command
    {
        COMMAND,
        ARG1,
        ARG2
    };

    /**************************************************************************
     * Program Start
     **************************************************************************/

    // Create game object modules
    DB;     // Create database
    MAP;    // Create Map
    UI;     // Create UI
    PLAYER; // Create player

    // Print start screen here. If player enters <enter> to start, load the rest of the game
    // UI.mainMenu();

    // UI.initializeGame();

    // UI.startGame()

    // Initialize Database
    DB.initializeActionProcessor();    // Player action processor
    DB.initializeAdjacencyProcessor(); // Room adjacency processor
    // DB.initializeDirectionProcessor();   // Player direction input processor
    DB.setFilePath(argv[0]); // Set database file path
    DB.import();             // Import DB data into program

    //
    std::string input = "";

    std::cout << "Terminating Program.\n";

    return 0;
}
