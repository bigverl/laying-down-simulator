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

    // Print start screen here. If player enters <enter> to start, load the rest of the game
    // UI.mainMenu(); // This will prob print menu and handle all input for the main menu including navigating between screens before player starts actual game

    // Initialize Database
    DB.initializeActionProcessor();    // Player action processor
    DB.initializeAdjacencyProcessor(); // Room adjacency processor
    // DB.initializeDirectionProcessor();   // Player direction input processor
    // Also need command processor
    DB.setFilePath(path); // Set database file path
    DB.import();          // Import DB data into program
    int winRoomPosition = DB.getRooms()->size() - 1;

    // Set game attributes
    _winStatus = false;
    _playerPosition = 0;
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
        system("cls");
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
                system("pause");
                system("cls");
            }
        } // END while(invalidInput)

        // Menu Switch
        switch (mainMenuOption)
        {
        case M_START:
            inMainMenu = false;
            std::cout << "This is a placeholder for START GAME\n";
            // Game.StartAdventure();
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
