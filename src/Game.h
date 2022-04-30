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
    bool _quitStatus;                   // governs whether or not player wishes to quit
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
    void setPlayerPosition(const int &roomID);

    // Initialize game
    void initialize(const char *path);

    // Function governs main menu behavior
    void mainMenu();

    // Returns true if player has won the game
    bool playerWon();

    // Returns true if player has chosen to quit the game
    bool playerQuit();

    // Debug function to print stats associated with game state.
    void printGameStatus();

    // This function starts the game when player selects this option from main menu
    void startAdventure();

    // Parses a line of input into the command structure
    std::vector<std::string> *getCommand(std::string line);

    // Split string
    std::vector<std::string> *split(std::string toSplit);

    // The primary game loop. Handles basically all the processing in the game
    void gameLoop();

    // Moves player
    void movePlayer(const int &destination);

    // Gets player input to process into command
    std::string getInput();

    // Prints "press enter to continue, waits for enter"
    void printPause();

    // ***** Validators ***** //
    // Validates command input for correct number of arguments -> (north arg1 arg2 prop3 is invalid)
    bool hasInvalidCommandArgs();

    // Validates a specific action for correct number of arguments (use, get, etc)
    bool hasInvalidActionArgs(const unsigned long int &argCount);

    // Validate command for valid action (GET, etc)
    bool isInvalidAction(const int &actionToValidate);

    // Validate character's attempts to quit game
    void validateQuitAttempt();

    // Validate player's ACTION input
    bool validateAction();

    // Validates directional input
    bool isInvalidDirection(const int &directionToValidate);

    // Validates main menu options as characters
    bool validateMainMenuOption(char userInput);

    // Returns true if room does not have an exit in given direction
    bool isInvalidExit(const int &direction);

    // Returns true if exit is blocked
    bool exitIsBlocked(const int &direction);

    // Returns true if prop is in this room
    bool propInRoom(const int &propID);

    // *** End Validators *** //

    // *** Begin Action-Related Methods ** //
    // This governs executing actions such as GET, PUSH, PULL, etc
    // Must return false if successful
    void executeAction(const int &action);

    // Player attempts to use standalone prop
    void use();

    // Player attempts to use a key to solve a lock
    void solve();

    // Player attempts to look at prop in room
    void look();

    // Player attempts to pick up prop in room
    void get();

    // Player attempts to push prop in room
    void push();

    // Player attempts to push prop in room
    void pull();

    // Player attempts to talk to prop in room
    void talk();

    // Player attempts to open prop in room
    void open();

    // Player attempts to close prop in room
    void close();

    // Player wishes to access inventory
    void inventory();

    // Player wishes to open help menu
    void help();

    // Governs intro before main menu
    void intro();

    // Governs ending and credits
    void ending();
};

enum MainMenuOptions
{
    M_START = 'S',
    M_HELP = 'H',
    M_QUIT = 'Q'
};

#endif
