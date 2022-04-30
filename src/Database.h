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
#include "Enums.h"

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
    std::vector<Prop> *props;                      // Interactable objects in rooms
    std::vector<Room> *rooms;                      // Locations in game
    std::filesystem::path executablePath;          // path to database
    std::map<std::string, int> actionProcessor;    // action list to quickly search and return enum value
    std::map<std::string, int> adjacencyProcessor; // abbreviated direction list to quickly search and return enum value
    std::map<std::string, int> directionProcessor; // direction list to quickly search and return enum value
    std::vector<std::string> *_directions;

    // Methods
    Database() = default; // private constructor

public:
    // Creates one instance of database. If one exists, it returns the existing one.
    static Database &getInstance();

    // Initializes action processing tool
    void initializeActionProcessor();

    // Initializes direction processing tool
    void initializeDirectionProcessor();

    // Initializes direction processing tool
    void initializeAdjacencyProcessor();

    // Parses an action passed as string to int value to be used in enum
    int parseAction(const std::string &toParse);

    // Parses a direction passed as string to int value to be used in enum
    int parseAdjacency(const std::string &toParse);

    // Parses a direction passed as string to int value to be used in enum
    int parseDirection(const std::string &toParse);

    // Set file path to open database files
    void setFilePath(const char *path);

    // Creates file path to specific database file
    std::filesystem::path createDBPath(const std::string fileName);

    // Split string
    std::vector<std::string> *split(std::string toSplit);

    // Reads entire file into a single string
    std::string readFileIntoString(const std::string &path);

    // Helper function to import prop data from csv
    void importProps();

    // Helper function to import room data from csv
    void importRooms();

    // Imports data from file to program memory.
    void import();

    // Return prop item by ID
    Prop *getProp(const int &id) const;

    // Return room item by ID
    Room *getRoom(const int &id) const;

    // Get directions vector
    std::vector<std::string> *getDirections();

    // Player will reference props by name, and so we must retrieve their ID's by name
    int getPropIDByName(std::string name);

    // Return prop name by id
    std::string getPropName(const int &id) const;

    // Return room name by id
    std::string getRoomName(const int &id) const;

    // Return pointer to all prop data
    std::vector<Prop> *getProps() const;

    // Return pointer to all room data
    std::vector<Room> *getRooms() const;

    // Debug: Returns ID for room adjacent to room ID and direction given
    int getAdjacentRoomID(const int &origin, const int &direction);

    // Returns prop in origin that's blocking destination
    int getRoomBlockerID(const int &origin, const int &destination);

    // Returns prop blocking this one. Returns -1 if prop is not blocked
    int getPropBlockerID(const int &propID);
};

#endif
