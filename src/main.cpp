#include <iostream>
#include "Database.h"
#include "Map.h"
#include "Player.h"
#include "Prop.h"
#include "Room.h"
#include "UI.h"

int main()
{
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

    std::cout
        << "helo werl\n";

    return 0;
}
