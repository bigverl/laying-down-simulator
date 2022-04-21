#include "Game.h"
#include "Database.h"
#include "Room.h"
#include "Prop.h"
#include "Player.h"
#include "UserInterface.h"
#include "Enums.h"

// Creates one instance of Game. If one exists, it returns the existing one.
Game &Game::getInstance()
{
    static Game instance;
    return instance;
}

//  Returns id of room player currently occupies
int Game::getPlayerPosition()
{
    return _playerPosition;
}

// Sets player position when player moves
void Game::setPlayerPosition(const int &roomID)
{
    _playerPosition = roomID;
}

void Game::initialize(const char *path)
{
    // Create game object modules
    DB;     // Create database
    UI;     // Create UI
    PLAYER; // Create player

    // Initialize Database
    DB.initializeActionProcessor();    // Player action processor
    DB.initializeAdjacencyProcessor(); // Room adjacency processor
    DB.initializeDirectionProcessor(); // Player direction input processor
    DB.setFilePath(path);              // Set database file path
    DB.import();                       // Import DB data into program

    // Set game attributes
    _winStatus = false;
    _playerPosition = 0;
    int winRoomPosition = DB.getRooms()->size() - 1;
    _winRoom = DB.getRoom(winRoomPosition)->getID();

    // Launch main menu
    mainMenu();
}

void Game::mainMenu()
{
    // Initialize menu variables
    bool invalidInput = true;
    bool inMainMenu = true;
    char charInput;
    int menuChoice = -1;

    // Main menu loop
    while (inMainMenu)
    {
        // Clear screen
        CLEAR_SCREEN;
        invalidInput = true;

        // Validate input
        while (invalidInput)
        {
            // Output menu
            UI.printMainMenu();

            // Get user input
            std::cout << "Choice: ";
            std::cin.get(charInput);

            invalidInput = validateMainMenuOption(charInput);

            if (invalidInput)
            {
                std::cout << "Invalid Input. Please use letters listed in menu."
                          << std::endl;
                printPause();
                CLEAR_SCREEN;
            }

        } // END while(invalidInput)

        // If it's valid, we're all good.
        menuChoice = toupper(charInput);

        // Menu Switch
        switch (menuChoice)
        {
        case M_START:
            inMainMenu = false;
            startAdventure();
            break;
        case M_QUIT:
            _quitStatus = true;
            inMainMenu = false;
            break;
        case M_HELP:
            UI.printHelp();
            break;
        default:
            break;
        }
    } // END while(inMainMenu)
}

bool Game::validateMainMenuOption(char userInput)
{
    bool invalidInput = true;

    // ToUpper input if it's not newline
    if (userInput != '\n')
    {
        std::cin.ignore(999, '\n');
        userInput = toupper(userInput);

        invalidInput = (userInput != 'S' && userInput != 'H' && userInput != 'Q');
    }

    return invalidInput;
}

void Game::validateQuitAttempt()
{
    bool validQuit = false;
    char charInput = ' ';

    // Output
    std::cout << "Are you sure you want to quit? Y/N: ";

    // Input, toUpper
    std::cin.get(charInput);

    if (charInput != '\n')
    {
        std::cin.ignore(999, '\n');
        charInput = toupper(charInput);

        validQuit = (charInput == 'Y' || charInput == 'N');
    }

    while (!validQuit)
    {

        std::cout << "Invalid Input. Try again.\n"
                  << "Are you sure you want to quit? Y/N: ";
        // Input, toUpper
        std::cin.get(charInput);

        if (charInput != '\n')
        {
            std::cin.ignore(999, '\n');
            charInput = toupper(charInput);

            validQuit = (charInput == 'Y' || charInput == 'N');
        }
    }

    if (charInput == 'Y')
    {
        _quitStatus = true;
    }
}

// Returns whether player has won
bool Game::playerWon()
{
    return _winRoom == _playerPosition;
}

// Returns whether player has quit
bool Game::playerQuit()
{
    return _quitStatus;
}

// Debug
void Game::printGameStatus()
{
    std::cout << "\n";
    std::cout << "Current Player Position: " << _playerPosition << "\n";
    std::cout << "Quit Status: " << _quitStatus << "\n";
    std::cout << "Win status: " << _winStatus << "\n";
    std::cout << "Win Room: " << _winRoom << "\n";
    std::cout << "\n";
}

void Game::startAdventure()
{
    CLEAR_SCREEN;
    // Placeholder start
    std::cout << "This is a placeholder for START GAME.\n"
              << "It's where all the intro text will go.\n";

    // Placeholder end

    std::cout << "\nPress <ENTER> to begin your adventure..";
    std::cin.ignore();
    CLEAR_SCREEN;

    // Start actual game loop
    gameLoop();
}

// This helper function separates each string from a line of text into a separate index of a vector.
std::vector<std::string> *Game::split(std::string toSplit)
{

    std::vector<std::string> *result = new std::vector<std::string>;
    std::string temp = "";
    for (unsigned long int index = 0; index < toSplit.length(); index++)
    {
        if (toSplit[index] == ' ')
        {
            result->push_back(temp);
            temp = "";
        }
        else
        {
            temp.push_back(toSplit[index]);
        }
    }

    result->push_back(temp);

    return result;
}

// Parses a line of input into the command structure
std::vector<std::string> *Game::getCommand(std::string line)
{
    // Split line
    std::vector<std::string> *command = split(line);

    // To-upper each entry in the vector
    for (unsigned long int index = 0; index < command->size(); index++)
    {
        // ToUpper the string
        for (auto &c : command->at(index))
        {
            c = (char)toupper(c);
        }

        // DEBUG: Print toupper'd commands in vector
        // std::cout << "Command string at index " << index << " is: " << command->at(index) << std::endl;
    }

    return command;
}

// Primary game loop. It's big
void Game::gameLoop()
{
    std::string userInput = ""; // Line of input
    int action = -1;            // Action converted to int for switch. Starts out invalid
    int direction = -1;         // Direction converted to int for switch. Starts out invalid
    bool invalidAction = true;
    bool invalidMove = true;
    bool invalidRoomExit = true;
    bool exitBlocked = true;
    bool invalidArgCount = true;
    bool quitOrInvOrHelp = true;

    // Begin Game Loop
    while (!playerQuit() && !playerWon())
    {
        // DEBUG STUB
        std::cout << "Welcome to the room description placeholder! You're currently in room: #" << getPlayerPosition() << std::endl;
        std::cout << "Printing Current Room: \n";
        DB.getRooms()->at(getPlayerPosition()).print();

        // Print the room's pic and description
        // printRoom(ID);

        // Create new command
        _command = new std::vector<std::string>;

        // Get input, create command
        userInput = getInput();
        _command = getCommand(userInput);

        // Validate number of arguments
        invalidArgCount = hasInvalidCommandArgs();

        // If invalid, inform the player
        if (invalidArgCount)
        {
            std::cout << "Hey, I think you put too many arguments into that command. Try something else!\n";
        }
        else // Else, continue and determine if player is attempting to move
        {
            // DEBUG STUB
            std::cout << "Yes, that is the correct number of arguments, debugger!\n";

            // Player is attempting to move because they only input one argument
            if (_command->size() == 1)
            {
                // Validate movement first by checking if they input a valid direction
                direction = DB.parseDirection(_command->at(ACTION));
                invalidMove = isInvalidDirection(direction);

                // If invalid, they may be attempting to access inventory or quit
                if (invalidMove)
                {
                    action = DB.parseAction(_command->at(ACTION));
                    quitOrInvOrHelp = (action == QUIT || action == INVENTORY || action == HELP);

                    if (!quitOrInvOrHelp)
                    {
                        std::cout << "Hmm. That doesn't seem to be a valid direction. Try another way.\n";
                    }
                    else // If it's quit or inventory, go ahead and send it through
                    {
                        executeAction(action);
                    }
                }
                else // Else, the direction is theoretically valid. Now check for valid exit and blocking prop
                {
                    // DEBUG STUB
                    std::cout << "Yes, that was a valid direction, debugger! The direction you entered was: " << direction << ".\n";

                    invalidRoomExit = isInvalidExit(direction);

                    // If it still doesn't work, that room doesn't have an exit in that direction
                    if (invalidRoomExit)
                    {
                        std::cout << "Weird, you don't see an exit in that direction. Maybe try a different path?\n";
                    }
                    else // Else, check to see if a prop is blocking that exit
                    {
                        // // DEBUG STUB. COMMENT THIS OUT
                        // int origin = DB.getRooms()->at(getPlayerPosition()).getID();
                        // int adjacentRoomID = DB.getAdjacentRoomID(origin, direction);
                        // std::cout << "Yes, an exit exists in that direction, debugger! Here's the information for that room:\n"
                        //           << "Room ID:" << DB.getRooms()->at(adjacentRoomID).getID() << "\n"
                        //           << "Room Name: " << DB.getRooms()->at(adjacentRoomID).getName() << "\n";
                        // // END DEBUG STUB

                        // // DEBUG STUB: DELETE THIS WHEN DONE DEBUGGING MOVEMENT
                        // int blockingPropID = DB.getBlockingPropID(origin, adjacentRoomID);
                        // DB.getProps()->at(blockingPropID).expire();
                        // // END DEBUG STUB

                        // Checks to see if unexpired blocking prop is blocking exit
                        exitBlocked = exitIsBlocked(direction);

                        if (exitBlocked)
                        {
                            // Get blockingprop ID
                            int currentRoom = DB.getRooms()->at(getPlayerPosition()).getID();
                            int destination = DB.getAdjacentRoomID(currentRoom, direction);
                            int blockingPropID = DB.getBlockingPropID(currentRoom, destination);

                            // DEBUG STUB:
                            std::cout << "Yes, a prop is blocking that exit, debugger! Here's the information for that prop:\n "
                                      << "Prop ID: " << blockingPropID << "\n"
                                      << "Prop Name: " << DB.getProps()->at(blockingPropID).getName() << "\n";
                            // END DEBUG STUB

                            // Print the blocking prop's blocker message
                            std::cout << DB.getProps()->at(blockingPropID).getBlockerText() << "\n";
                        }
                        else // If none of the above, we're good to move
                        {
                            // DEBUG STUB:
                            std::cout << "Congratulations, debugger. You moved!\n";

                            // Move the player
                            int currentRoom = DB.getRooms()->at(getPlayerPosition()).getID();
                            int destination = DB.getAdjacentRoomID(currentRoom, direction);
                            movePlayer(destination);
                        }
                    }
                }
            }
            else // Else, they're attempting to take an action
            {
                // Validate attempted action
                action = DB.parseAction(_command->at(0));
                invalidAction = isInvalidAction(action);

                if (invalidAction)
                {
                    std::cout << "Hey, that's not a valid action. Try something else!\n";
                }
                else // Else, go ahead and try to execute the action
                {
                    // DEBUG STUB
                    std::cout << "Yes, that is a valid action, debugger!\n";
                    executeAction(action);
                }
            }
        }

        if (!playerQuit())
        {
            printPause();
            CLEAR_SCREEN;
        }
        // Game will check for win or quit condition here automatically
    }
}

// Returns true if object is blocking exit
bool Game::exitIsBlocked(const int &direction)
{
    const int BLOCKED_EXIT_VALUE = -1;
    // Get blockingprop ID
    int currentRoom = DB.getRooms()->at(getPlayerPosition()).getID();
    int destination = DB.getAdjacentRoomID(currentRoom, direction);
    int blockingPropID = DB.getBlockingPropID(currentRoom, destination);
    bool blockingPropExpired = DB.getProps()->at(blockingPropID).isExpired();

    // If the prop is expired, it is no longer blocking.
    if (blockingPropExpired)
    {
        return false;
    }

    return blockingPropID != BLOCKED_EXIT_VALUE;
}

// Returns true if exit does not exist in given direction
bool Game::isInvalidExit(const int &direction)
{
    bool invalidRoomExit = true;
    unsigned long int index = 0;

    // Get adjacent rooms
    std::vector<AdjacentRoom> *adjacentRooms = nullptr;
    adjacentRooms = DB.getRooms()->at(getPlayerPosition()).getAdjacentRooms();

    // Check if exit exists in player's desired direction
    while (invalidRoomExit && index < adjacentRooms->size())
    {
        invalidRoomExit = (direction != adjacentRooms->at(index)._direction);
        index++;
    }

    return invalidRoomExit;
}

// Validates overall command for correct number of arguments
bool Game::hasInvalidCommandArgs()
{
    const int VALID_COMMAND_ARG_COUNT = 3;
    return (_command->size() > VALID_COMMAND_ARG_COUNT);
}

// Validates player attempting to use an action command
bool Game::isInvalidAction(const int &actionToValidate)
{
    // -1 is the value returned by the actionProcessor when it cannot find a match
    const int INVALID_ACTION_VALUE = -1;

    return actionToValidate == INVALID_ACTION_VALUE;
}

// Validates player attempting to enter directional movement command
bool Game::isInvalidDirection(const int &directionToValidate)
{
    // -1 is the value returned by the directionProcessor when it cannot find a match
    const int INVALID_DIRECTION_VALUE = -1;

    return directionToValidate == INVALID_DIRECTION_VALUE;
}

// Validates a specific action for correct number of arguments (use, get, etc)
bool hasInvalidActionArgs(const int &argCount);

// Gets player input
std::string Game::getInput()
{
    std::string userInput = "";
    std::cout << "> ";
    std::getline(std::cin, userInput);

    return userInput;
}

void Game::printPause()
{
    std::cout << "Press <ENTER> to continue";
    std::cin.ignore(); // Pause for <enter>
}

// This governs executing actions such as GET, PUSH, PULL, etc
// Must return false if successful
void Game::executeAction(const int &action)
{
    bool invalidArgCount = true;

    // Validate all the arg counts
    // Get the props they're referencing in the command

    switch (action)
    {
    case USE:
        // 2 or 3 arg options here
        if (_command->size() == 2)
        {
            // DEBUG STATEMENT:
            std::cout << "SOMETHING WENT WEIRD IN 'USE', JUST SAYIN' \n";
            use();
        }
        else if (_command->size() == 3)
        {
            solve();
        }
        else
        {
            std::cout << "SOMETHING WENT WEIRD IN 'USE', JUST SAYIN' \n";
        }

        break;
    case LOOK:
        look();
        break;
    case GET:
        get();
        break;
    case PUSH:
        push();
        break;
    case PULL:
        pull();
        break;
    case TALK:
        talk();
        break;
    case OPEN:
        open();
        break;
    case CLOSE:
        close();
        break;
    case HELP:
        help();
        break;
    case QUIT:
        validateQuitAttempt();
        break;
    case INVENTORY:
        inventory();
    default:
        break;
    }
}

// Player attempts to use standalone prop
void Game::use()
{
    const int VALID_ARG_COUNT = 1; // Valid argument count for this type of action
    // DEBUG STATEMENT
    std::cout << "Congratulations, debugger: You're inside use():'\n";

    // // Validate arguments
    // bool invalidArgCount = hasInvalidActionArgs(VALID_ARG_COUNT);

    // if (invalidArgCount)
    // {
    //     std::cout << "Too many arguments. If you're trying to 'use' something, you'll want to use the form 'use <prop>'\n";
    // }
    // else
    // {
    //     // DEBUG STATEMENT
    //     std::cout << "Congratulations, debugger: This is the prop you wanted:'\n";

    // Actual code go here. //

    // arg1 must be in player inventory

    // If so, return the useDescription and exhaust the prop.
}
// Player attempts to use a key to solve a lock
void Game::solve()
{
    const int VALID_ARG_COUNT = 2; // Valid argument count for this type of action
    // DEBUG STATEMENT
    std::cout << "Congratulations, debugger: You're inside solve():'\n";

    //     // Validate arguments
    //     bool invalidArgCount = hasInvalidActionArgs(VALID_ARG_COUNT);

    //     if (invalidArgCount)
    //     {
    //         std::cout << "Too many arguments. If you're trying to 'use' something, you'll want to use the form 'use <prop>'\n";
    //     }
    //     else
    //     {
    //         // DEBUG STATEMENT
    //         std::cout << "Congratulations, debugger: This is the key prop you used:'\n";
    //         std::cout << "And this is the lock prop you used it on: '\n";

    // Actual code go here //

    // arg1 (key) must be in player inventory

    // etc

    // exhaust key, exhaust lock
}
// Player attempts to look at prop in room
void Game::look()
{
    // DEBUG STATEMENT
    std::cout << "Congratulations, debugger: You're inside look():'\n";
}
// Player attempts to pick up prop in room
void Game::get()
{
    // DEBUG STATEMENT
    std::cout << "Congratulations, debugger: You're inside get():'\n";
}
// Player attempts to push prop in room
void Game::push()
{
    // DEBUG STATEMENT
    std::cout << "Congratulations, debugger: You're inside push():'\n";
}
// Player attempts to push prop in room
void Game::pull()
{
    // DEBUG STATEMENT
    std::cout << "Congratulations, debugger: You're inside pull():'\n";
}
// Player attempts to talk to prop in room
void Game::talk()
{
    // DEBUG STATEMENT
    std::cout << "Congratulations, debugger: You're inside talk():'\n";
}
// Player attempts to open prop in room
void Game::open()
{
    // DEBUG STATEMENT
    std::cout << "Congratulations, debugger: You're inside open():'\n";
}

// Player attempts to close prop in room
void Game::close()
{
    // DEBUG STATEMENT
    std::cout << "Congratulations, debugger: You're inside close():'\n";
}

// Player wishes to access inventory
void Game::inventory()
{
    // DEBUG STATEMENT
    std::cout << "Congratulations, debugger: You're inside inventory():'\n";
}

// Player wishes to open help menu
void Game::help()
{
    // DEBUG STATEMENT
    std::cout << "Congratulations, debugger: You're inside help():'\n";
}

void Game::movePlayer(const int &destination)
{
    _playerPosition = destination;
}
