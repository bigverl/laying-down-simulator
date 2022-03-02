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
    std::string descriptionPic;                // ascii the reason these are separate is in case they change over course of gameplay
    std::string descriptionText;               // text	 the reason these are separate is in case they change over course of gameplay
    std::vector<int> *props;                   // array of interactables in the room (id's)
    std::vector<AdjacentRooms> *adjacentRooms; // -1 if unavailable. if available: 0 north 1 west 2 south 3 east. for use in navigation enum

public:
    // Methods

    // Return room id
    int getID() const
    {
        return 0;
    }

    // returns name of prop given its id (for use in player commands)
    std::string findPropName(const int &propID)
    {
        return "";
    }

    // returns full list of room's props (ids)
    std::vector<int> *getProps()
    {
        return nullptr;
    }

    // returns directions that player can move. will determine this by referencing adjacency matrix
    std::vector<int> *getAdjacentCells()
    {
        return nullptr;
    }

    // returns room description
    std::string getDescription() const
    {
        return "";
    }

    // returns room pic in ascii
    std::string getPic() const
    {
        return "";
    }

    // Constructors
    Room(){};
};

#endif // ROOM.H