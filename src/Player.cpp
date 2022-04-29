#include "Player.h"
#include "Database.h"

// Creates one instance of Player. If one exists, it returns the existing one.
Player &Player::getInstance()
{
    static Player instance;
    return instance;
}

// Returns player's inventory
const std::vector<int> &Player::getInventory() const
{
    return _inventory;
}

// Adds prop to player's inventory
void Player::addPropToInventory(int propID)
{
    _inventory.push_back(propID);
}

// Returns true if prop is in player's inventory
bool Player::propInInventory(int propID)
{
    bool found = false;
    unsigned long int index = 0;
    while (!found && index < _inventory.size())
    {
        found = (DB.getProps()->at(_inventory.at(index)).getID() == propID);
        index++;
    }
    return found;
}