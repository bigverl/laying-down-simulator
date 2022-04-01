#ifndef DATABASE_H
#define DATABASE_H

#include "Prop.h"
#include "Room.h"
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <filesystem>
#include <ctype.h>

// This is a macro. You refer to the database instance as this name when programming
#define DB (Database::getInstance())

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
    std::vector<Prop> *props;                   // Interactable objects in rooms
    std::vector<Room> *rooms;                   // Locations in game
    std::filesystem::path executablePath;       // path to database
    std::map<std::string, int> actionProcessor; // Command list to quickly search and return enum value

    // Methods
    Database() = default; // private constructor

public:
    // Creates one instance of database. If one exists, it returns the existing one.
    static Database &getInstance();

    void initializeActionProcessor();

    int parseAction(const std::string &toParse);

    // Set file path to open database files
    void setFilePath(const char *path);

    // Creates file path to specific database file
    std::filesystem::path createDBPath(const std::string fileName);

    // Split string
    std::vector<std::string> *split(std::string toSplit);

    // Helper function to import prop data from csv
    void importProps();

    // Helper function to import room data from csv
    void importRooms();

    // imports db from csv. this is a very large operation that will populate a ton of objects and data.
    // basically, it will define the map's room array as a certain size and fill it with those numbers for reference
    // then it will fill each room object's prop array and fill it with those numbers for reference
    // It will also actually populate all data in the database's props and room vectors
    // NOTE: consider making a loading screen if this takes a long time.

    // TODO: Imports data from file to program memory.
    void import();

    std::string readFileIntoString(const std::string &path);

    // TODO: Make sure this looks up and returns a prop by id. the placeholder Prop(); is just here to prevent compile errors rn
    Prop *getProp(const int &id) const;

    // TODO: Make sure this looks up and returns a room by id. the placeholder Prop(); is just here to prevent compile errors rn
    Room *getRoom(const int &id) const;

    std::string getPropName(const int &id) const;

    std::string getRoomName(const int &id) const;

    std::vector<Prop> *getProps() const;

    std::vector<Room> *getRooms() const;
};

// Enum represents database cell locations for props.csv
enum PropsDB
{
    P_ID,
    P_NAME,
    P_PICKED_UP,
    P_HOME_ROOM,
    P_SOLUTION_ROOM,
    P_SOLUTION_PROP,
    P_BLOCKING_ROOM,
    P_BLOCKING_PROP,
    P_VALID_COMMANDS,
    P_LOOK_DESCRIPTION,
    P_USE_DESCRIPTION,
    P_BLOCKER_TEXT,
    P_SUCCESS_TEXT,
    P_TALK_TEXT
};

// Enum represents database cell locations for rooms.csv
enum RoomsDB
{
    R_ID,
    R_NAME,
    R_PROPS,
    R_ADJACENT_CELLS,
    R_DESCRIPTION_TEXT_DEFAULT,
    R_DESCRIPTION_TEXT_SOLVED,
    R_DESCRIPTION_PIC
};

enum Actions
{
    USE,
    LOOK,
    GET,
    PUSH,
    PULL,
    TALK,
    OPEN,
    CLOSE,
    HELP,
    QUIT,
    INVENTORY
};

#endif
