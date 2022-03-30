#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>

/****************************************************************************************************
 * Player class represents the player character. Governs inventory management, commands and movement.
 * Follows singleton pattern. See database class for more info
 *****************************************************************************************************/
class Player
{
    // Attributes
    std::vector<int> inventory; // vector of items in inventory by id. can't be a regular array because variable size
    static Player instance;

    // Methods
public:
    static Player getInstance()
    {
        return instance;
    }

    // returns id of item given its name. helper function for 'execute' method
    int getItem(const std::string &name)
    {
        return 0;
    }

    // attempts to execute command if possible (enum is used for command). This will likely be complicated
    // unless all commands are only two words. This is probably going to be a very very large method with lots of switch statements.
    // Definitely the most complicated algorithm in the entire program
    void execute(const int &command, const std::string &target)
    {
    }

    // attempts to move in given direction if possible (enum is used for direction). Will output 'cant' and reprint screen on failure
    void move(const int &direction)
    {
    }

private:
    // private constructor
    Player(){};
};

#endif
