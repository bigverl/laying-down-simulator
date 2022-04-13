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
void Game::setPlayerPosition(const int &newPosition)
{
    _playerPosition = newPosition;
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
            _quit = true;
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
        _quit = true;
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
    return _quit;
}

// Debug
void Game::printGameStatus()
{
    std::cout << "\n";
    std::cout << "Current Player Position: " << _playerPosition << "\n";
    std::cout << "Quit Status: " << _quit << "\n";
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
std::vector<std::string> *Game::getCommand(std::string &line)
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
    bool invalidArgCount = true;
    bool quitOrInv = true;

    // Begin Game Loop
    while (!playerQuit() && !playerWon())
    {
        // DEBUG STUB
        std::cout << "Welcome to the room description placeholder! \n";

        // Print the room
        // printRoom(ID);

        // Create new command
        _command = new std::vector<std::string>;

        // Get input, create command
        userInput = getInput();
        _command = getCommand(userInput);

        // Validate number of arguments
        invalidArgCount = validateCommandArgs();

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
                direction = DB.parseDirection(_command->at(0));
                invalidMove = validateDirection(direction);

                // If invalid, they may be attempting to access inventory or quit
                if (invalidMove)
                {
                    action = DB.parseAction(_command->at(0));
                    quitOrInv = (action == QUIT || action == INVENTORY || action == HELP);

                    if (!quitOrInv)
                    {
                        std::cout << "Hmm. That doesn't seem to be a valid direction. Try another way.\n";
                    }
                    else // If it's quit or inventory, go ahead and send it through
                    {
                        invalidAction = executeAction(action);
                    }
                }
                else // Else, go ahead and try to move
                {
                    // DEBUG STUB
                    std::cout << "Yes, that was a valid direction, debugger!\n";

                    // invalidMove = move(direction)

                    // If it still doesn't work, that room doesn't have an exit in that direction
                    // if(invalidMove)
                    // {
                    //     std::cout << "Weird, you don't see an exit in that direction. Maybe try a different path?\n";
                    // }
                }
            }
            else // Else, they're attempting to take an action
            {
                // Validate attempted action
                action = DB.parseAction(_command->at(0));
                invalidAction = validateAction(action);

                if (invalidAction)
                {
                    std::cout << "Hey, that's not a valid action. Try something else!\n";
                }
                else // Else, go ahead and try to execute the action
                {
                    // DEBUG STUB
                    std::cout << "Yes, that is a valid action, debugger!\n";
                    // invalidAction = execute(action);
                }
            }
        }

        // Delete old command
        delete _command;

        if (!playerQuit())
        {
            printPause();
            CLEAR_SCREEN;
        }
        // Game will check for win or quit condition here
    }
}

// Validates overall command for correct number of arguments
bool Game::validateCommandArgs()
{
    return (_command->size() > 3);
}

// Validates player attempting to use an action command
bool Game::validateAction(const int &actionToValidate)
{
    // -1 is the value returned by the actionProcessor when it cannot find a match
    const int INVALID_ACTION_VALUE = -1;

    return actionToValidate == INVALID_ACTION_VALUE;
}

// Validates player attempting to enter directional movement command
bool Game::validateDirection(const int &directionToValidate)
{
    // -1 is the value returned by the directionProcessor when it cannot find a match
    const int INVALID_DIRECTION_VALUE = -1;

    return directionToValidate == INVALID_DIRECTION_VALUE;
}

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
bool Game::executeAction(const int &action)
{
    switch (action)
    {
    case QUIT:
        validateQuitAttempt();
        break;
    default:
        // std::cout << "That is not a valid command. Please try again\n";
        break;
    }
}

// This governs player movement such as NORTH, SOUTH, EAST, WEST
// Must return false if successful
bool Game::attemptMove(const int &direction)
{
    return false;
}

// This is a helper function to move the player. Used for debugging, mostly
void Game::movePlayer(const int &roomID)
{
}