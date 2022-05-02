#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <vector>

/********************************************************************************************
 * The 'AdjacentRooms’ struct contains a room’s adjacent roomID’s and the direction of that room
 ********************************************************************************************/
struct AdjacentRoom
{
    int _roomID;
    int _direction;

    AdjacentRoom(const int &roomID, const int &direction)
    {
        _roomID = roomID;
        _direction = direction;
    }
};

/********************************************************************************************
 * The 'Room' class contains all attributes and methods required to manage a single room
 ********************************************************************************************/
class Room
{
    // Attributes
    int _id;                                   // id of room. its position in the rooms[] matrix
    std::string _name;                         // name of room
    std::vector<int> *_props;                  // array of interactables in the room (id's)
    std::vector<AdjacentRoom> *_adjacentRooms; // -1 if unavailable. if available: 0 north 1 west 2 south 3 east. for use in navigation enum
    std::string _descriptionTextDefault;       // text the reason these are separate is in case they change over course of gameplay
    std::string _descriptionTextSolved;        // text the reason these are separate is in case they change over course of gameplay
    std::string _descriptionPic;               // ascii the reason these are separate is in case they change over course of gameplay

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
    std::vector<AdjacentRoom> *getAdjacentRooms() const;

    // returns room default description
    std::string getDescriptionTextDefault() const;

    // Sets room description
    void setDescriptionTextDefault(const std::string &descriptionText);

    // Sets room picture
    void setDescriptionPic(const std::string &descriptionPic);

    // returns room description after one 'solve' (optional)
    std::string getDescriptionTextSolved() const;

    // returns room pic in ascii
    std::string getPic() const;

    // Prints room attributes
    void print();

    // Constructors
    Room(const int &id,
         const std::string &name,
         std::vector<int> *props,
         std::vector<AdjacentRoom> *adjacentRooms,
         const std::string &descriptionTextDefault,
         const std::string &descriptionTextSolved,
         const std::string &descriptionPic);
};

#endif // ROOM.H
