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
void UserInterface::printRoomDescription(const int &id)
{
    // This is just how you'd likely get the room object. Gotta do the rest
    DB.getRoom(id);
}

// prints the available navigation directions derived from room's id
// compared to adj list
void UserInterface::printNavigation(const int &id)
{
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
void UserInterface::printCommands() {}

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

    // Placeholder
    std::cout << "___________________________________________\n"
              << "Help: \n"
              << "___________________________________________\n"
              << "Command                           Description\n"

              << "\n";
}

void UserInterface::printPause()
{
    std::cout << "\nPress <ENTER> to continue\n";
    std::cin.ignore(); // Pause for <enter>
}