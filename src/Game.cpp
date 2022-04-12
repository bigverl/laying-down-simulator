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
    const int inputArSize = 3;
    char inputAr[inputArSize] = {'S', 'H', 'Q'};
    bool invalidInput = true;
    bool inMainMenu = true;
    char mainMenuOption;
    const std::string PROMPT = "Choice: ";

    // Main menu loop
    while (inMainMenu)
    {
        // Clear screen
        CLEAR_SCREEN;
        invalidInput = true;

        while (invalidInput)
        {
            // Input
            invalidInput = validateMainMenuOption(inputAr, inputArSize,
                                                  mainMenuOption);
            if (invalidInput)
            {
                std::cout << "Invalid Input. Please use letters listed in menu."
                          << std::endl;
                printPause();
                CLEAR_SCREEN;
            }
        } // END while(invalidInput)

        // Menu Switch
        switch (mainMenuOption)
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

bool Game::validateMainMenuOption(char validAr[], const int &arSize, char &charInput)
{
    bool invalidInput = true;
    int index = 0;

    // Output
    UI.printMainMenu();

    // Input
    std::cin.get(charInput);
    std::cin.ignore(999, '\n');
    charInput = toupper(charInput);

    // Compare to valid array
    while (index < arSize && invalidInput)
    {
        invalidInput = charInput != validAr[index];
        index++;
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
    std::cin.ignore(999, '\n');
    charInput = toupper(charInput);

    validQuit = (charInput == 'Y' || charInput == 'N');

    while (!validQuit)
    {

        std::cout << "Invalid Input. Try again.\n"
                  << "Are you sure you want to quit? Y/N: ";
        // Input, toUpper
        std::cin.get(charInput);
        std::cin.ignore(999, '\n');
        charInput = toupper(charInput);

        validQuit = (charInput == 'Y' || charInput == 'N');
    }

    if (charInput == 'Y')
    {
        _quit = true;
    }
}

bool Game::playerWon()
{
    return _winRoom == _playerPosition;
}

bool Game::getQuitStatus()
{
    return _quit;
}

void Game::setQuitStatus(const bool &newStatus)
{
    _quit = newStatus;
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

    // Pull action from command
    if (command->size() > 0)
    {
    }
    // If split vector > 0
    // Match first arg with existing command or with cardinal direction
    // Push it back

    // If split vector >= 1
    // place second arg

    // If split vector >= 2
    // place third arg

    // return the split vector
    return command;
}

// Primary game loop. It's big
void Game::gameLoop()
{
    std::string userInput = ""; // Line of input
    const std::string quitPrompt = "Are you sure you want to quit? Y/N: ";
    int action = -1; // Action converted to int for switch. Starts out invalid
    bool invalidCommand = true;
    bool invalidAction = true;

    // Begin game loop
    do
    {
        // Create new command
        _command = new std::vector<std::string>;
        invalidCommand = true;
        invalidAction = true;

        // TODO printRoom(ID);

        // Get input, create command
        userInput = getInput();
        _command = getCommand(userInput);

        // Validate command
        invalidCommand = validateCommand();

        // Parse action int from action string
        action = DB.parseAction(_command->at(ACTION));

        // Validate action int and print error if unacceptable
        invalidAction = validateAction(action);

        // Validate command for correct number of args
        while (invalidCommand || invalidAction)
        {
            // Get input, create command
            userInput = getInput();
            _command = getCommand(userInput);

            // Validate command
            invalidCommand = validateCommand();

            // Parse action int from action string
            action = DB.parseAction(_command->at(ACTION));

            // Validate action int and print error if unacceptable
            invalidAction = validateAction(action);
        }

        // Parse and validate action int for switch

        // // DEBUG
        // std::cout << "Full command:" << userInput << std::endl;
        // std::cout << "Action Int:" << action << std::endl;

        // Process player command, and respond
        switch (action)
        {
        case QUIT:
            validateQuitAttempt();
            break;
        default:
            std::cout << "That is not a valid command. Please try again\n";
            printPause();
            break;
        }

        if (!_quit && !playerWon())
        {
            // Pause, reset
            std::cout << std::endl;
            std::cin.ignore();
            CLEAR_SCREEN;
        }
        // Pause, clear screen

        // Delete command
        delete _command;
    } while (!_quit && !playerWon());
}

bool Game::validateCommand()
{
    // Inform player
    if (_command->size() > 3)
    {
        std::cout << "Invalid command: Too many arguments.\n";
        printPause();
        CLEAR_SCREEN;
    }

    return (_command->size() > 3);
}

bool Game::validateAction(const int &actionToValidate)
{
    const int INVALID_ACTION_VALUE = -1;
    bool invalidAction = actionToValidate == INVALID_ACTION_VALUE;

    if (invalidAction)
    {
        std::cout << "Invalid command: Action invalid.\n";
        printPause();
        CLEAR_SCREEN;
    }

    return invalidAction;
}

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