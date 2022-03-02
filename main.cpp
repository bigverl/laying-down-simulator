#include <iostream>
#include "Database.h"
#include "Map.h"
#include "Player.h"
#include "Prop.h"
#include "Room.h"
#include "UI.h"

int main()
{
    // Enum outlining commands. these are examples and should be customized for our actual game. probably goes in main
    enum Commands
    {
        EXAMINE,
        GET,
        PUSH,
        PULL,
        USE,
        TALK,
        GIVE,
        DROP,
        QUIT,
        INVENTORY,
    };

    enum Directions
    {
        NORTH,
        WEST,
        SOUTH,
        EAST,
    };

    std::cout << "helo werl\n";

    return 0;
}