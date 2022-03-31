#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

/********************************************************************************************
 * The 'AdjacentRooms’ struct contains a room’s adjacent roomID’s and the direction of that room
 ********************************************************************************************/
struct AdjacentRooms
{
    int roomID;
    int direction;
};

/********************************************************************************************
 * The 'Room' class contains all attributes and methods required to manage a single room
 ********************************************************************************************/
class Room
{
    // Attributes
    int id;                                    // id of room. its position in the rooms[] matrix
    std::string name;                          // name of room
    std::string descriptionPic;                // ascii the reason these are separate is in case they change over course of gameplay
    std::string descriptionText;               // text	 the reason these are separate is in case they change over course of gameplay
    std::vector<int> *props;                   // array of interactables in the room (id's)
    std::vector<AdjacentRooms> *adjacentRooms; // -1 if unavailable. if available: 0 north 1 west 2 south 3 east. for use in navigation enum

public:
    // Methods

    // Return room id
    int getID() const;

    // Returns room name
    std::string getName() const;

    // returns name of prop given its id (for use in player commands)
    std::string findPropName(const int &propID);

    // returns full list of room's props (ids)
    std::vector<int> *getProps() const;

    // returns directions that player can move. will determine this by referencing adjacency matrix
    std::vector<int> *getAdjacentCells() const;

    // returns room description
    std::string getDescription() const;

    // returns room pic in ascii
    std::string getPic() const;

    // Constructors
    Room();
};

#endif // ROOM.H
