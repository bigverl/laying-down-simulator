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

// DEBUG: Print player inventory
void Player::printInventory()
{
    std::cout << "Printing inv: \n";
    for (unsigned long int index = 0; index < PLAYER.getInventory()->size(); index++)
    {
        std::cout << "Prop ID: " << PLAYER.getInventory()->at(index).getID() << "\n";
        std::cout << "Prop Name: " << PLAYER.getInventory()->at(index).getName() << "\n";
    }
}