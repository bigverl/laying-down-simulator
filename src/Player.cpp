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

std::vector<int> *Player::getInventory() const
{
    return _inventory;
}