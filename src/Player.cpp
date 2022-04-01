#include "Player.h"

// Creates one instance of Player. If one exists, it returns the existing one.
Player &Player::getInstance()
{
    static Player instance;
    return instance;
}

// returns id of item given its name. helper function for 'execute' method
int Player::getItem(const std::string &name)
{
    return 0;
}

// attempts to execute command if possible (enum is used for command). This will likely be complicated
// unless all commands are only two words. This is probably going to be a very very large method with lots of switch statements.
// Definitely the most complicated algorithm in the entire program
void Player::execute(const int &command, const std::string &target)
{
}

// attempts to move in given direction if possible (enum is used for direction). Will output 'cant' and reprint screen on failure
void Player::move(const int &direction)
{
}
