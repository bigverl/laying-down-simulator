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

    // Methods
    Game() = default; // private constructor

public:
    // Creates one instance of game. If one exists, it returns the existing one.
    static Game &getInstance();

    // Returns ID of room player currently occupies
    int getPlayerPosition();

    void setPlayerPosition(const int &newPosition);

    // Initialize game
    void initialize(const char *path);
};

#endif
