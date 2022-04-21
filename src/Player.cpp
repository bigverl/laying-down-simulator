#include "Player.h"

// Creates one instance of Player. If one exists, it returns the existing one.
Player &Player::getInstance()
{
    static Player instance;
    return instance;
}

// Returns player's inventory
std::vector<Prop> *Player::getInventory() const
{
    return _inventory;
}

// Initializes player inventory to new item
void Player::initializePlayerInventory()
{
    _inventory = new std::vector<Prop>;
}

// Adds prop to player's inventory
void Player::addPropToInventory(Prop *toAdd)
{
    _inventory->push_back(*toAdd);
}