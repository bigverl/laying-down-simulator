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

    // Create database. When referring to DB calls, just use the term DB as if
    // it's the object
    DB;     // Create database
    MAP;    // Create Map
    UI;     // Create UI
    PLAYER; // Create player

    // Initialize Action Processor
    DB.initializeActionProcessor();
    DB.initializeAdjacencyProcessor();

    // Get file path
    DB.setFilePath(argv[0]);

    // Import DB data into program
    DB.import();

    std::cout << "helo werl\n";

    return 0;
}
