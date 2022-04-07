#include "Database.h"
#include "Game.h"
#include "Player.h"
#include "Prop.h"
#include "Room.h"
#include "UserInterface.h"
#include <iostream>

int main(int argc, char *argv[])
{
    /**************************************************************************
     * Program Start
     **************************************************************************/

    std::cout << "Starting Program.\n";
    LDS; // Create game object

    LDS.initialize(argv[0]);

    std::cout << "Terminating Program.\n";

    return 0;
}
