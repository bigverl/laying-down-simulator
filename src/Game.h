#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <iostream>
#include <vector>

// This is a macro. You refer to the database instance as this name when programming
#define LDS (Game::getInstance())

/********************************************************************************************
 * The Game class governs operations of the overall game operations. Includes game loop
 * and initializes all other modules Follows singleton pattern.
 *
 * https://www.tutorialspoint.com/Explain-Cplusplus-Singleton-design-pattern
 *
 *
 * Fires initialize() when game starts
 ********************************************************************************************/
class Game
{
    // Attributes
    int _playerPosition;                // id of current room player occupies. will change during movement
    bool _quit;                         // governs whether or not player wishes to quit
    bool _winStatus;                    // determines if player has won
    int _winRoom;                       // roomID for post-final room
    std::vector<std::string> *_command; // Command structure player uses to interact with game world

    // Methods
    Game() = default; // private constructor

public:
    // Creates one instance of game. If one exists, it returns the existing one.
    static Game &getInstance();

    // Returns ID of room player currently occupies
    int getPlayerPosition();

    // Sets player position into a new room. Used for tracking movement and updating state
    void setPlayerPosition(const int &newPosition);

    // Initialize game
    void initialize(const char *path);

    // Function governs main menu behavior
    void mainMenu();

    // Returns true if player has won the game
    bool playerWon();

    // Returns whether or not player has decided to quit
    bool getQuitStatus();

    // Helper function to set 'quit = true'
    void setQuitStatus(const bool &newStatus);

    // Debug function to print stats associated with game state.
    void printGameStatus();

    // This function starts the game when player selects this option from main menu
    void startAdventure();

    // Parses a line of input into the command structure
    std::vector<std::string> *getCommand(std::string &line);

    // Split string
    std::vector<std::string> *split(std::string toSplit);

    // The primary game loop. Handles basically all the processing in the game
    void gameLoop();

    // Gets player input to process into command
    std::string getInput();

    // Prints "press enter to continue, waits for enter"
    void printPause();

    // ***** Validators ***** //
    // Validates commands for correct number of arguments
    bool validateCommand();

    // Validate command for valid action (GET, etc)
    bool validateAction(const int &actionToValidate);

    // Validate character's attempts to quit game
    void validateQuitAttempt();

    // Validate player's ACTION input
    bool validateAction();

    // Validates main menu options as characters
    bool validateMainMenuOption(char userInput);
};

enum MainMenuOptions
{
    M_START = 'S',
    M_HELP = 'H',
    M_QUIT = 'Q'
};

#endif
