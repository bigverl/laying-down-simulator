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

    // Create game object and initialize
    LDS;
    LDS.initialize(argv[0]);

    // TESTING START

    // TESTING END

    std::cout << "Terminating Program.\n";

    return 0;
}
