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

    std::cout << "\nPress <ENTER> to begin your adventure..\n";
    std::cin.ignore();
    CLEAR_SCREEN;

    // Start game loop
    gameLoop();

    // Start ending
    ending();
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
    bool quitOrInvOrHelp = true;

    // Begin Game Loop
    while (!playerQuit() && !playerWon())
    {
        // DEBUG STUB
        // Print room name
        std::cout << "Current Room: " << getPlayerPosition() << " - "
                  << DB.getRooms()->at(getPlayerPosition()).getName() << "\n\n";
        // Print props

        // Print arr
        std::cout << "Props: \n";
        for (unsigned long int index = 0; index < DB.getRooms()->at(getPlayerPosition()).getProps()->size(); index++)
        {
            std::cout << DB.getProps()->at(DB.getRooms()->at(getPlayerPosition()).getProps()->at(index)).getName() << " ";
        }
        std::cout << std::endl
                  << std::endl;

        std::cout << "Exits: \n";
        for (unsigned long int index = 0; index < DB.getRooms()->at(getPlayerPosition()).getAdjacentRooms()->size(); index++)
        {
            int directionChecker = DB.getRooms()->at(getPlayerPosition()).getAdjacentRooms()->at(index)._direction;
            if (directionChecker != -1)
            {
                std::cout << DB.getDirections()->at(DB.getRooms()->at(getPlayerPosition()).getAdjacentRooms()->at(index)._direction) << " ";
            }
            else
            {
                std::cout << "None";
            }
        }

        std::cout << std::endl
                  << std::endl;
        // END DEBUG

        // Print the room's pic and description
        // printRoom(ID);

        // Create new command
        _command = new std::vector<std::string>;

        // Get input, create command
        userInput = getInput();
        _command = getCommand(userInput);

        // If invalid, inform the player
        if (hasInvalidCommandArgs())
        {
            std::cout << "Hey, I think you put too many arguments into that command. Try something else!\n";
        }
        else if (_command->size() == 1) // If arg is 1, check for movement and 0-arg actions
        {
            // Get user's desired direction
            direction = DB.parseDirection(_command->at(ACTION));

            if (_command->at(ACTION) == "") // Command is empty
            {
                std::cout << "Well, you've got to do -something-, right?\n";
            }
            else if (isInvalidDirection(direction)) // Invalid directional input
            {
                action = DB.parseAction(_command->at(ACTION));
                quitOrInvOrHelp = (action == QUIT || action == INVENTORY || action == HELP);

                if (!quitOrInvOrHelp) // Not an action
                {
                    std::cout << "Hmm. I don't think thats a valid command. Enter 'help' for a list of commands.\n";
                }
                else // Send action through
                {
                    executeAction(action);
                }
            }
            else if (isInvalidExit(direction)) // Determine if exit exists in given direction
            {
                std::cout << "Weird, you don't see an exit in that direction. Maybe try a different path?\n";
            }
            else if (exitIsBlocked(direction)) // Exit blocked by prop
            {
                // Get blockingprop ID
                int currentRoom = DB.getRooms()->at(getPlayerPosition()).getID();
                int destination = DB.getAdjacentRoomID(currentRoom, direction);
                int blockingPropID = DB.getRoomBlockerID(currentRoom, destination);

                std::cout << DB.getProps()->at(blockingPropID).getBlockerText() << "\n";
            }
            else // Success: Move player
            {
                int currentRoom = DB.getRooms()->at(getPlayerPosition()).getID();
                int destination = DB.getAdjacentRoomID(currentRoom, direction);
                std::cout << "You head " << DB.getDirections()->at(direction) << ".\n";
                movePlayer(destination);
            }
        }
        else // Else, they're attempting to take an action
        {
            // Validate attempted action
            action = DB.parseAction(_command->at(ACTION));

            if (isInvalidAction(action)) // Invalid action
            {
                std::cout << "Hey, that's not a valid action. Try something else!\n";
            }
            else // Success: execute
            {
                executeAction(action);
            }
        }

        if (!playerQuit())
        {
            printPause();
            CLEAR_SCREEN;
        }
    } // End while
}

// Returns true if object is blocking exit
bool Game::exitIsBlocked(const int &direction)
{
    const int NOT_FOUND = -1;
    // Get blockingprop ID
    int currentRoom = DB.getRooms()->at(getPlayerPosition()).getID();
    int destination = DB.getAdjacentRoomID(currentRoom, direction);
    int blockingPropID = DB.getRoomBlockerID(currentRoom, destination);

    if (blockingPropID == NOT_FOUND)
    {
        // there is no blocking prop ID
        return false;
    }

    bool blockingPropExpired = DB.getProps()->at(blockingPropID).isExpired();
    // If the prop is expired, it is no longer blocking.
    if (blockingPropExpired)
    {
        return false;
    }

    return true;
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

// Validates overall command for correct number of arguments
bool Game::hasInvalidActionArgs(const unsigned long int &argCount)
{
    return (_command->size() > argCount);
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

// Checks to see if given action is valid with given prop
bool invalidActionForProp(const int &propID, const std::string &action)
{
    std::vector<int> *supportedCommands = DB.getProps()->at(propID).getValidCommands();
    int actionInt = DB.parseAction(action);
    bool invalidAction = true;

    // For each command in this prop's 'valid commands' list
    for (unsigned long int index = 0; index < supportedCommands->size(); index++)
    {
        // Check to see if the given action is supported
        invalidAction = (actionInt != supportedCommands->at(index));

        // If it doesn't match, it's valid aka !invalid
        if (!invalidAction)
        {
            return false;
        }
    }

    return true;
}

void Game::printPause()
{
    std::cout << "Press <ENTER> to continue\n";
    std::cin.ignore(); // Pause for <enter>
}

// This governs executing actions such as GET, PUSH, PULL, etc
// Must return false if successful
void Game::executeAction(const int &action)
{
    switch (action)
    {
    case USE:
        // 2 or 3 arg options here
        if (_command->size() == 2)
        {
            use();
        }
        else if (_command->size() == 3)
        {
            solve();
        }
        else
        {
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
    // DEBUG STATEMENT
    // std::cout << "Congratulations, debugger: You're inside use():'\n";

    // Declaration
    const unsigned long int VALID_ARG_COUNT = 2; // Valid argument count for this type of action
    const int NOT_FOUND = -1;
    std::string propName = _command->at(ARG1);
    int propID = DB.getPropIDByName(propName);
    std::string actionName = _command->at(ACTION);
    std::string errorMsg = "Hmm, you don't seem to have any '" + propName + "' to use.\n";
    bool invalidArgCount = hasInvalidActionArgs(VALID_ARG_COUNT);
    const int FLASHLIGHT = 5;
    const int DESK = 13;
    const int TUNNEL_HUB_LIGHT = 3;
    const int CREDITS = 8;

    if (invalidArgCount)
    {
        std::cout << "Too many arguments. If you're trying to 'use' something, try 'use <prop>'\n";
    }
    else if (propID == NOT_FOUND)
    {
        std::cout << errorMsg;
    }
    else if (!PLAYER.propInInventory(propID)) // Check to see if it's in player inventory
    {
        std::cout << errorMsg;
    }
    else if (DB.getProps()->at(propID).isExpired()) // Check to see if the prop has already been exhausted
    {
        std::cout << errorMsg;
    }
    else if (invalidActionForProp(propID, actionName)) // If not, check if that's a valid action for this prop
    {
        std::cout << "I don't think that can be used by itself.";
    }
    else // else, expire it and print the useDescription
    {
        DB.getProps()->at(propID).expire();
        std::cout << DB.getProps()->at(propID).getUseDescription() << "\n";

        // I know this is bad but it's happening
        if (propID == FLASHLIGHT)
        {
            movePlayer(TUNNEL_HUB_LIGHT);
        }
        else if (propID == DESK)
        {
            movePlayer(CREDITS);
        }
        else
        {
        }
    }
}
// Player attempts to use a key to solve a lock
void Game::solve()
{
    // DEBUG STATEMENT
    // std::cout << "Congratulations, debugger: You're inside solve():'\n";

    // Declaration
    const unsigned long int VALID_ARG_COUNT = 3; // Valid argument count for this type of action
    const int NOT_FOUND = -1;
    const int SCROLL = 9;
    const int CREDITS = 8;
    std::string keyName = _command->at(ARG1);
    std::string lockName = _command->at(ARG2);
    int keyID = DB.getPropIDByName(keyName);
    int lockID = DB.getPropIDByName(lockName);
    std::string actionName = "SOLVE";
    bool invalidArgCount = hasInvalidActionArgs(VALID_ARG_COUNT);

    // Code
    if (invalidArgCount) // Valid arguments
    {
        std::cout << "Invalid argument count. If you're trying to 'use' something on another thing, try 'use <prop1> <prop2>'\n";
    }
    else if (keyID == NOT_FOUND) // Key is in game
    {
        std::cout << "You don't seem to have a " << keyName << " to use. \n";
    }
    else if (lockID == NOT_FOUND) // Lock is in game
    {
        std::cout << "You don't see a " << lockName << " here..\n";
    }
    else if (!PLAYER.propInInventory(keyID)) // Key is in player inventory
    {
        std::cout << "You don't seem to have a " << keyName << " to use. \n";
    }
    else if (!propInRoom(lockID)) // Lock is in room
    {
        std::cout << "You don't see a " << lockName << " here..\n";
    }
    else if (DB.getProps()->at(keyID).isExpired()) // Key is not expired
    {
        std::cout << "You don't seem to have a " << keyName << " to use. \n";
    }
    else if (invalidActionForProp(keyID, actionName)) // Key supports 'solve' command
    {
        std::cout << "I don't think that can be used like that.";
    }
    else if ((DB.getProps()->at(keyID).getSolutionProp()) != lockID) // Key's solutionProp == Lock
    {
        std::cout << "Using the " << keyName << " on the " << lockName << " doesn't seem to do anything..\n";
    }
    else // Success: Exhaust props, print message
    {
        DB.getProps()->at(keyID).expire();
        DB.getProps()->at(lockID).expire();
        std::cout << DB.getProps()->at(keyID).getSuccessText() << "\n";

        // I know this is bad but it's happening
        if (keyID == SCROLL)
        {
            movePlayer(CREDITS);
        }
    }
}
// Player attempts to look at prop in room
void Game::look()
{
    // Declaration
    const int NOT_FOUND = -1;
    int propID = -1;
    std::string propName = _command->at(ARG1);
    propID = DB.getPropIDByName(propName);

    if (propID == NOT_FOUND) // Prop does not exist in game
    {
        std::cout << "Hmm, you don't see any '" << propName << "' to look at here.\n";
    }
    else if (!propInRoom(propID)) // Prop is in room
    {
        std::cout << "Hmm, you don't see any '" << propName << "' to look at here.\n";
    }
    else if (DB.getProps()->at(propID).isPickedUp()) // Prop has not been picked up yet
    {
        std::cout << "Hmm, you don't see any '" << propName << "' to look at here.\n";
    }
    else // Success: Return description
    {
        std::cout << DB.getProps()->at(propID).getLookDescription() << "\n";
    }
}
// Player attempts to pick up prop in room
void Game::get()
{
    // Declaration
    const int NOT_FOUND = -1;
    int propID = -1;
    int blockerID = -1;
    const std::string actionName = _command->at(ACTION);
    const std::string propName = _command->at(ARG1);
    propID = DB.getPropIDByName(propName);

    if (propID == NOT_FOUND) // Prop is not in game
    {
        std::cout << "Hmm, you don't see any '" << propName << "' to pick up here.\n";
    }
    else if (!propInRoom(propID)) // Prop is not in room
    {
        std::cout << "Hmm, you don't see any '" << propName << "' to pick up here.\n";
    }
    else if (invalidActionForProp(propID, actionName)) // Action is invalid for prop
    {
        std::cout << "Uh, you don't feel like you can pick up the '" << propName << "'.\n";
    }
    else if (DB.getProps()->at(propID).isPickedUp()) // Prop is already picked up
    {
        std::cout << "Hmm, you don't see any '" << propName << "' to pick up here.\n";
    }
    else if ((blockerID = DB.getPropBlockerID(propID)) != NOT_FOUND) // It's blocked
    {
        std::cout << DB.getProps()->at(propID).getBlockerText() << "\n";
    }
    else // Success: Pick it up
    {
        PLAYER.addPropToInventory(propID);
        DB.getProps()->at(propID).setPickedUpStatus(true);

        std::cout << "You pick up the '" << propName << "' and add it to your inventory.\n";
    }

    // DEBUG: Print player inventory
    // PLAYER.printInventory();
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
    // std::cout << "Congratulations, debugger: You're inside talk():'\n";

    // Declaration
    const int NOT_FOUND = -1;
    int propID = -1;
    const std::string actionName = _command->at(ACTION);
    const std::string propName = _command->at(ARG1);
    propID = DB.getPropIDByName(propName);

    if (propID == NOT_FOUND) // Prop is not in game
    {
        std::cout << "Hmm, you don't see any '" << propName << "' to talk to here.\n";
    }
    else if (!propInRoom(propID)) // Prop is not in room
    {
        std::cout << "Hmm, you don't see any '" << propName << "' to talk to here.\n";
    }
    else if (invalidActionForProp(propID, actionName)) // Action is invalid for prop
    {
        std::cout << "Uh, you don't feel like you can talk to the '" << propName << "'.\n";
    }
    else // Success: Return talk text
    {
        std::cout << DB.getProps()->at(propID).getTalkText();
    }
}
// Player attempts to open prop in room
void Game::open()
{
    // Declaration
    const unsigned long int VALID_ARG_COUNT = 2; // Valid argument count for this type of action
    const int NOT_FOUND = -1;
    int blockerID = -1;
    const std::string propName = _command->at(ARG1);
    int propID = DB.getPropIDByName(propName);
    const std::string actionName = _command->at(ACTION);
    const std::string errorMsg = "Hmm, you don't see any '" + propName + "' to open.\n";
    bool invalidArgCount = hasInvalidActionArgs(VALID_ARG_COUNT);

    if (invalidArgCount) // Valid number of arguments
    {
        std::cout << "Too many arguments. If you're trying to 'open' something, try 'open <prop>'\n";
    }
    else if (propID == NOT_FOUND) // Prop in game
    {
        std::cout << errorMsg;
    }
    else if (!propInRoom(propID)) // Prop in room
    {
        std::cout << errorMsg;
    }
    else if (DB.getProps()->at(propID).isExpired()) // Prop is expired
    {
        std::cout << "That's already open!\n";
    }
    else if (invalidActionForProp(propID, actionName)) // validate prop supports action
    {
        std::cout << "I don't think you can open the " << propName << ".\n";
    }
    else if ((blockerID = DB.getPropBlockerID(propID)) != NOT_FOUND) // Prop not blocked
    {
        // check for whether or not it is exhausted tho. this messes with the else-if. resolve that
        std::cout << DB.getProps()->at(blockerID).getBlockerText() << "\n";
    }
    else // Success: Expire prop and print the useDescription
    {
        DB.getProps()->at(propID).expire();
        std::cout << DB.getProps()->at(propID).getUseDescription() << "\n";
    }
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
    UI.printPlayerInventory();
}

// Player wishes to open help menu
void Game::help()
{
    // DEBUG STATEMENT
    std::cout << "Congratulations, debugger: You're inside help():'\n";

    // UI.printHelp();
}

void Game::movePlayer(const int &destination)
{
    _playerPosition = destination;
}

// Returns true if prop is in room player currently occupies
bool Game::propInRoom(const int &propID)
{
    bool found = false;
    unsigned long int index = 0;
    while (!found && index < DB.getRooms()->at(_playerPosition).getProps()->size())
    {
        found = (DB.getRooms()->at(_playerPosition).getProps()->at(index) == propID);
        index++;
    }
    return found;
}

// Executes ending
void Game::ending()
{
    const int FISH = 4;

    std::cout << "Congrats, you made it on time for your midterm and you feel pretty good about your grade.\n";
    printPause();
    CLEAR_SCREEN;

    // If fish is exhausted, play good ending
    if (DB.getProps()->at(FISH).isExpired())
    {
        // Play good ending here
        std::cout << "And you saved the fish! What a great pet owner!\n";
    }
    else
    {
        std::cout << "Unfortunately, you forgot to feed your fish. \n"
                  << "Some things must be sacrificed in times of great need..\n";

        // Play bad ending here
    }
    printPause();
    CLEAR_SCREEN;

    std::cout << "___________________________________________________\n"
              << "                  Midterm Madness: \n"
              << "         Brought to you by Red Circle Studios\n"
              << "___________________________________________________\n"
              << "Programming, Design, Architecture:   Weston Mathews\n"
              << "Room and Prop Descriptions, Puzzles: Dania\n"
              << "Room Artwork:                        Nick"
              << "Title Screen:                        Hamid\n"
              << "Management, Puzzles, Story:          Stephanie \n\n"
              << "Thanks for playing!!\n\n";
    printPause();
}
