#ifndef PROP_H
#define PROP_H

#include <vector>
#include <string>

/****************************************************************************************************
 * The 'Props' class represents any interactable object in a room including items, doors, people, etc
 *****************************************************************************************************/
class Prop
{
    // Attributes
    int id;
    std::string name; // name of prop
    bool pickedUp;    // whether or not item has been picked up by player. Used so player can't pick up items twice
    int homeRoom;     // the ID of the item's original location. Used for changing game state in other rooms.
    bool expired;
    std::vector<int> validCommands; // this is a list of acceptable commands for this specific item. likely represented by an enum in main or something
    int solutionRoom;               // the ID of the room where the item must be used. Used to determine if player has completed obstacle
    std::string description;        // description of item. Used for EXAMINE command

    // Methods
public:
    std::string getName() const
    {
        return name;
    }
    int getID() const
    {
        return id;
    }

    // determines if item is able to be picked up. NOTE: THIS MIGHT BE MITIGATED BY REMOVING THE 'PICKUP' COMMAND ONCE ITS PICKED UP INSTEAD?
    bool isPickedUp() const
    {
        return false;
    }

    // determines if item is in its original room
    bool inHomeRoom() const
    {
        return false;
    }

    // returns id of room where this item needs to be used
    int getSolutionRoomID() const
    {
        return 0;
    }

    // returns item's description
    std::string getDescription() const
    {
        return "";
    }

    int *getValidCommands() const
    {
        return 0;
    }

    // expires item (item has been fully used and cannot be used again)
    void expire()
    {
    }

    // constructors
    Prop(){};
};

#endif // PROP_H
