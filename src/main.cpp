#include "Database.h"
#include "Map.h"
#include "Player.h"
#include "Prop.h"
#include "Room.h"
#include "UI.h"

#include <iostream>

int main()
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
    DB;

    // Create Map
    MAP;

    std::cout << "helo werl\n";

    return 0;
}
