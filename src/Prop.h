#ifndef PROP_H
#define PROP_H

#include <vector>
#include <string>
#include <iostream>

/****************************************************************************************************
 * The 'Props' class represents any interactable object in a room including items, doors, people, etc
 *****************************************************************************************************/
class Prop
{
    // Attributes
    int _id;
    std::string _name;                // name of prop
    bool _pickedUp;                   // whether or not item has been picked up by player. Used so player can't pick up items twice
    int _homeRoom;                    // the ID of the item's original location. Used for changing game state in other rooms.
    int _solutionRoom;                // ID of room where prop is meant to be used with SOLVE command
    int _solutionProp;                // If this prop is a KEY, solutionProp is the LOCk this KEY will unlock
    int _blockingRoom;                // If this prop blocks a room, this is ID of room blocked
    int _blockingProp;                // If this prop blocks another prop, this is the ID of the prop blocked
    std::vector<int> *_validCommands; // This is a list of acceptable commands for this specific item. represented by an enum in main
    std::string _lookDescription;     // String returned when player uses LOOK command
    std::string _useDescription;      // String returned when player successfully USES this prop
    std::string _blockerText;         // If this prop is a blocker, this will be returned when they attempt to move past without first SOLVING
    std::string _successText;         // String returned when player successfully SOLVES a puzzle using this prop
    std::string _talkText;            // String returned when player uses TALK command
    bool _expired;                    // Determines whether or not prop has been used to its fullest extent

    // Methods
public:
    // Returns prop's ID
    int getID() const;

    // Returns prop's name
    std::string getName() const;

    // Returns true if item has been picked up
    bool isPickedUp() const;

    // Returns true if item is in its original room
    bool inHomeRoom() const;

    // Returns true if prop is expired
    bool isExpired() const;

    // Returns ID room where this item needs to be used
    int getSolutionRoomID() const;

    // Returns prop's description when player enters "LOOK <target>"
    std::string getLookDescription() const;

    // Returns all valid commands for prop
    std::vector<int> *getValidCommands() const;

    int getBlockingRoom() const;

    std::string getBlockerText() const;

    // Expires item after it has been used fully, and cannot be used again
    void expire();

    // Print for debug
    void print();

    // Full param constructor
    Prop(const int &id,
         const std::string &name,
         const bool &pickedUp,
         const int &homeRoom,
         const int &solutionRoom,
         const int &solutionProp,
         const int &blockingRoom,
         const int &blockingProp,
         std::vector<int> *validCommands,
         const std::string &lookDescription,
         const std::string &useDescription,
         const std::string &blockerText,
         const std::string &successText,
         const std::string &talkText);
};

#endif // PROP_H
