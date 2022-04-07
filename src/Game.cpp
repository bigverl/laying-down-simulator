#include "Game.h"
#include "Database.h"
#include "Room.h"
#include "Prop.h"
#include "Player.h"
#include "UserInterface.h"

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
    // UI.mainMenu();

    // UI.initializeGame();

    // UI.startGame()

    // Initialize Database
    DB.initializeActionProcessor();    // Player action processor
    DB.initializeAdjacencyProcessor(); // Room adjacency processor
    // DB.initializeDirectionProcessor();   // Player direction input processor
    DB.setFilePath(path); // Set database file path
    DB.import();          // Import DB data into program

    //
    std::string input = "";
}