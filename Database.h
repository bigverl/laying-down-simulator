#ifndef DATABASE_H
#define DATABASE_H

#include "Prop.h"
#include "Room.h"
#include <vector>

/********************************************************************************************
 * The Database class contains game data necessary to play the game. Includes props and rooms
 * Follows singleton pattern. Must be instantiated above main function to zero.
 *
 * https://www.tutorialspoint.com/Explain-Cplusplus-Singleton-design-pattern
 *
 *
 * Fires import() when player presses start at title screen
 * note: we are likely going to need to make the room vector a pointer because we have to
 *       pass it to the Map for map construction
 ********************************************************************************************/
class Database
{
    // Attributes
    std::vector<Prop> *props; // array of Interactables in the game (to be accessed by id). this is a vector because it gets appended during import
    std::vector<Room> *rooms; // array of Rooms in the game (to be accessed by id). this is a vector because it gets appended during import
    static Database instance;

    // Methods
public:
    static Database getInstance()
    {
        return instance;
    }

    // imports db from csv. this is a very large operation that will populate a ton of objects and data.
    // basically, it will define the map's room array as a certain size and fill it with those numbers for reference
    // then it will fill each room object's prop array and fill it with those numbers for reference
    // It will also actually populate all data in the database's props and room vectors
    // NOTE: consider making a loading screen if this takes a long time.

    // TODO make sure proper csv file type is added to the params list
    void import()
    {
    }

    // TODO: Make sure this looks up and returns a prop by id. the placeholder Prop(); is just here to prevent
    // compile errors rn
    Prop getProp(const int &id) const
    {
        return Prop();
    }

    // TODO: Make sure this looks up and returns a room by id. the placeholder Prop(); is just here to prevent
    // compile errors rn
    Room getRoom(const int &id) const
    {
        return Room();
    }

    std::string getPropName(const int &id) const
    {
        return "";
    }

    std::string getRoomName(const int &id) const
    {
        return "";
    }

    std::vector<Room> *getRooms() const
    {
        return nullptr;
    }

    // Private constructor
private:
    Database(){}; // private constructor
};

#endif