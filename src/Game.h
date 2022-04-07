#ifndef GAME_H
#define GAME_H

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
    int _playerPosition; // id of current room player occupies. will change during movement
    bool _quit;          // governs whether or not player wishes to quit
    bool _winStatus;     // determines if player has won
    int _winRoom;        // roomID for post-final room

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

    void mainMenu();

    bool validateMainMenuOption(char validAr[], const int &arSize, char &charInput);

    bool playerWon();

    bool getQuitStatus();

    void setQuitStatus(const bool &newStatus);
    void printGameStatus();
    void startAdventure();
};

enum MainMenuOptions
{
    M_START = 'S',
    M_HELP = 'H',
    M_QUIT = 'Q'
};

#endif
