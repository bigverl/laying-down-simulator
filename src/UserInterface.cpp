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
void UserInterface::printRoomDescription(const int &roomID)
{
    std::string roomName = DB.getRoom(roomID)->getName();
    std::cout << "________________________________________________________________________________________________________\n";
    std::cout << "                                            " << DB.getRoomNames()->at(roomID) << "\n";
    std::cout << "________________________________________________________________________________________________________\n";
    // This is just how you'd likely get the room object. Gotta do the rest
    std::cout << DB.getRoom(roomID)->getDescriptionTextDefault();
    std::cout << "________________________________________________________________________________________________________\n";
}

// prints the available navigation directions derived from room's id
// compared to adj list
void UserInterface::printNavigation(const int &roomID)
{
    std::cout << "Exits: ";
    for (unsigned long int index = 0; index < DB.getRooms()->at(roomID).getAdjacentRooms()->size(); index++)
    {
        // Don't print if empty
        int noExits = DB.getRooms()->at(roomID).getAdjacentRooms()->at(index)._direction;
        if (noExits != -1)
        {
            std::cout << DB.getDirections()->at(DB.getRooms()->at(roomID).getAdjacentRooms()->at(index)._direction) << " ";
        }
        else
        {
            std::cout << "None";
        }
    }
    std::cout << std::endl;
}

// prints player inventory, probably also says 'press enter to continue'
// then reprints current room
void UserInterface::printPlayerInventory()
{
    CLEAR_SCREEN;

    // Placeholder
    std::cout << "___________________________________________\n"
              << "Inventory: \n"
              << "___________________________________________\n"
              << "Name                           Description\n"
              << "\n";
    for (unsigned long int index = 0; index < PLAYER.getInventory().size(); index++)
    {
        if (!DB.getProps()->at(PLAYER.getInventory().at(index)).isExpired())
        {
            std::cout << DB.getProps()->at(PLAYER.getInventory().at(index)).getName() << "                      "
                      << DB.getProps()->at(PLAYER.getInventory().at(index)).getLookDescription()
                      << "\n";
        }
    }
    std::cout << "___________________________________________\n";
}

// prints title screen
void UserInterface::printTitleScreen()
{
    std::cout << R"(
================================================================
   __   _              __   _               __   ___
 _(  )_( )_          _(  )_( )_          _(   )_(   )_
(_Red_Circle_)      (_Presents_)        (_A_Game_For__)
  (_) (__)            (_) (__)            (_) (_) (__)


      ....           ....           ....           ....
     ||             ||             ||             ||
 /"""c|\        /"""s|\        /"""u|\        /"""f|\
/_______\      /_______\      /_______\      /_______\
|  .-.  |------|  .-.  |------|  .-.  |------|  .-.  |----------
 __|C|__| .--. |__|P|__| .--. |__|S|__| .--. |__|C|__| .--.-----
_\  so\\__`ft-wa'__\  \\re__`e-n'__\  \\gi__`ne-er'__\  \\in__`g
-----------------l---------------------s------------------------
------c--------------------a----------------------s-------------
================================================================
    )";
}

// prints available commands
void UserInterface::printCommands()
{
    std::cout << "Commands: ";
    for (unsigned long int index = 0; index < DB.getActions()->size(); index++)
    {
        // Don't print if empty

        std::cout << DB.getActions()->at(index) << " ";
    }
    std::cout << std::endl;
}

// prints main menu
void UserInterface::printMainMenu()
{
    std::cout << R"(
	___________________________________________________________________________
	                ┌┬┐┬┌┬┐┌┬┐┌─┐┬─┐┌┬┐  ┌┬┐┌─┐┌┬┐┌┐┌┌─┐┌─┐┌─┐
	        - -	││││ ││ │ ├┤ ├┬┘│││  │││├─┤ │││││├┤ └─┐└─┐ - -
		        ┴ ┴┴─┴┘ ┴ └─┘┴└─┴ ┴  ┴ ┴┴ ┴─┴┘┘└┘└─┘└─┘└─┘  
    																					                                     
				             )                              
				            (                                 
				    ________[]_                              
				   /^=^-^-^=^-^\                   
				  /^-^-^-^-^-^-^\                 
				 /__^_^_^_^^_^_^_\               
				  |  .==.       |       ___       
				^^|  |LI|  [}{] |^^^^^ /___\ 
				&&|__|__|_______|&&   ." | ".   
				     ====             (o_|_o)              
				      ====             u   u 

			 S: START      H: HELP      Q: QUIT
	___________________________________________________________________________
    )";
    std::cout << std::endl;
}

void UserInterface::printHelp()
{
    CLEAR_SCREEN;
    std::cout << R"(
    ====================================================================================
    =                    ||\   ||\           ||\                                       =
    =                    || |  || |          || |                                      =
    =                    || |  || | ||||||\  || ||||||||\                              =
    =                    |||||||| |||  __||\ || |||  __||\                             =
    =                    ||  __|| ||||||||| ||| ||| /  || |                            =
    =                    || |  || |||   ____||| ||| |  || |                            =
    =                    || |  || |\|||||||\ || ||||||||  |                            =
    =                    \__|  \__| \_______|\__|||  ____/                             =
    =                                            || |                                  =
    =                                            || |                                  =
    =                                            \__|                                  =
    ====================================================================================
    =                                                                                  =
    = Directional movement:                                                            =
    = To move between rooms, simply enter a cardinal direction.                        =
    = 'North', 'East', 'South', 'West':                                                =
    =                                                                                  =
    = Pick up items:                                                                   =
    = Enter 'get <item>' where <item> is the one you want to pick up                   =
    =                                                                                  =
    = Interact with items in rooms:                                                    =
    = Enter one of the many commands including push, pull, open, close, and look.      =
    =                                                                                  =
    = Solve puzzles:                                                                   =
    = Just enter 'use <key> <lock>' where <key> is the item in your inventory          =
    = and the <lock> is the item in the room.                                          =
    =                                                                                  =
    = Access Inventory                                                                 =
    = Enter 'inventory' to view all the items you've picked up so far                  =
    =                                                                                  =
    = Quit:                                                                            =
    = Enter 'quit' to leave the game.                                                  =
    ====================================================================================

    )";
}

void UserInterface::printPause()
{
    std::cout << "\nPress <ENTER> to continue\n";
    std::cin.ignore(); // Pause for <enter>
}

// Governs printing entire room
void UserInterface::printRoom(const int &roomID)
{
    printRoomDescription(roomID);
    printNavigation(roomID);
    printCommands();
    std::cout << std::endl;
}

// Prints good ending
void UserInterface::printGoodEnding()
{
    std::cout << "";
    std::cout << R"(
        __________________________________________________________
                    +-------------------------------+
                    |o   o    /|                    |
                    |  o o   /  |         oo OO     |
                    |OO  o  /.    \ /|          O   |
                    | oo   )       | |           o  |
                    |       |  \ }/ \|            o |
                    |      }} \|       {{     oO    |
                    |     { }    O                O |
                    |      {                        |
                    |  O                            |
                    |===============================|
            ▄▀  ██   █▀▄▀█ ▄███▄      ████▄     ▄   ▄███▄   █▄▄▄▄ 
          ▄▀    █ █  █ █ █ █▀   ▀     █   █      █  █▀   ▀  █  ▄▀ 
          █ ▀▄  █▄▄█ █ ▄ █ ██▄▄       █   █ █     █ ██▄▄    █▀▀▌  
          █   █ █  █ █   █ █▄   ▄▀    ▀████  █    █ █▄   ▄▀ █  █  
           ███     █    █  ▀███▀              █  █  ▀███▀     █   
                  █    ▀                       █▐            ▀    
                 ▀                             ▐ 
        __________________________________________________________
            )";
}

// Prints bad ending
void UserInterface::printBadEnding()
{
    std::cout << "    ";
    std::cout << R"(
        __________________________________________________________
                    +------------------/|-----------+ 
                    |  O             /x    \ /|     |
                    |         oo     )      | |     |
                    |Oo           o    \ |   \|     |
                    |  o        O                O  |
                    |  ._        o      O         o |
                    |  oo     .      ooo         o  |
                    |         oo            ooo     |
                    |      } }       o              |
                    |     { }                       |
                    |      {             o          |
                    |   O                     o     |
                    |===============================|
            ▄▀  ██   █▀▄▀█ ▄███▄      ████▄     ▄   ▄███▄   █▄▄▄▄ 
          ▄▀    █ █  █ █ █ █▀   ▀     █   █      █  █▀   ▀  █  ▄▀ 
          █ ▀▄  █▄▄█ █ ▄ █ ██▄▄       █   █ █     █ ██▄▄    █▀▀▌  
          █   █ █  █ █   █ █▄   ▄▀    ▀████  █    █ █▄   ▄▀ █  █  
           ███     █    █  ▀███▀              █  █  ▀███▀     █   
                  █    ▀                       █▐            ▀    
                 ▀                             ▐ 
        __________________________________________________________
            )";
}