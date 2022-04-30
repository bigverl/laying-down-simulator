#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <iostream>
#include "Prop.h"

// This is a macro. You refer to the player instance as this name when programming
#define PLAYER (Player::getInstance())

/****************************************************************************************************
 * Player class represents the player character. Governs inventory management, commands and movement.
 * Follows singleton pattern. See database class for more info
 *****************************************************************************************************/
class Player
{
    // Attributes
    std::vector<int> _inventory; // vector of items in inventory by id

    // Methods
    Player() = default; // private constructor

public:
    // Creates one instance of database. If one exists, it returns the existing one.
    static Player &getInstance();

    // Returns player's inventory
    const std::vector<int> &getInventory() const;

    // Adds prop to player's inventory
    void addPropToInventory(int propID);

    // Returns true if a given prop is in the player's inventory
    bool propInInventory(int propID);
};

#endif
