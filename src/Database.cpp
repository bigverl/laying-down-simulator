#include "Database.h"

Database &Database::getInstance()
{
    static Database instance;
    return instance;
}

// Set file path to location where database files exist
void Database::setFilePath(const char *path)
{
    executablePath = std::filesystem::path(path);
    executablePath.replace_filename("");
    executablePath.append("db");
}

// Sets a file path to specific database file
std::filesystem::path Database::createDBPath(const std::string fileName)
{
    std::filesystem::path pathToFile(DB.executablePath);
    pathToFile.append(fileName);
    return pathToFile;
}

std::string Database::readFileIntoString(const std::string &path)
{
    auto ss = std::ostringstream{};
    std::ifstream input_file(path);

    if (!input_file.is_open())
    {
        std::cout << "Could not open the file - '" << path << "'" << std::endl;
    }
    else
    {
        std::cout << "Database file opened successfully\n";
        ss << input_file.rdbuf();
    }

    return ss.str();
}

// Creates a processor to retrieve command enums from strings
void Database::initializeActionProcessor()
{
    actionProcessor = {
        {"USE", USE},
        {"LOOK", LOOK},
        {"GET", GET},
        {"PUSH", PUSH},
        {"PULL", PULL},
        {"TALK", TALK},
        {"OPEN", OPEN},
        {"CLOSE", CLOSE},
        {"HELP", HELP},
        {"QUIT", QUIT},
        {"INVENTORY", INVENTORY}};
}

// Parses an action and returns its equivalent enum int value
int Database::parseAction(const std::string &toParse)
{
    std::string temp = toParse;
    std::map<std::string, int>::iterator it;

    // ToUpper the action
    for (auto &c : temp)
    {
        c = (char)toupper(c);
    }

    // Find it
    it = actionProcessor.find(temp);

    // Return int
    if (it == actionProcessor.end())
    {
        return -1;
    }

    return it->second;
}

std::vector<std::string> *Database::split(std::string toSplit)
{

    std::vector<std::string> *result = new std::vector<std::string>;
    std::string temp = "";
    for (unsigned long int index = 0; index < toSplit.length(); index++)
    {
        if (toSplit[index] == ' ')
        {
            result->push_back(temp);
            temp = "";
        }
        else
        {
            temp.push_back(toSplit[index]);
        }
    }

    result->push_back(temp);

    return result;
}

// Import props file into memory
void Database::importProps()
{
    // Initialize container to hold rows
    std::map<int, std::vector<std::string>> propData; // Each row of csv
    char delimiter = '|';                             // Delimeter for parsing cells
    std::string commandString;                        // Commands in cell
    std::vector<std::string> *commandsRaw = nullptr;  // Commands to place in valid commands vector

    std::vector<int> *commands = nullptr;
    Prop *temp = nullptr;          // temp item to populate
    std::vector<std::string> rows; // Entire row of data
    std::string rowData;           // Raw data from row

    // Preprocessing: Construct commandProcessor

    // Import raw data to string
    std::filesystem::path propsPath(createDBPath("props-test.csv"));
    std::string contents = readFileIntoString(propsPath);

    // Store data in stream for parsing
    std::istringstream sstream(contents);

    // DEBUG: Print raw data
    // std::cout << contents;

    int counter = 0;
    while (std::getline(sstream, rowData))
    {
        std::istringstream line(rowData);
        while (std::getline(line, rowData, delimiter))
        {
            rows.push_back(rowData);
        }

        propData[counter] = rows;
        rows.clear();
        counter++;
    }

    // Split command cell and place in commands vector
    commandsRaw = split(propData[4].at(P_VALID_COMMANDS));
    commands = new std::vector<int>;
    for (unsigned long int index = 0; index < commandsRaw->size(); index++)
    {
        commands->push_back(parseAction(commandsRaw->at(index)));
    }

    // Convert all database attributes to proper data structures
    int id = stoi(propData[1].at(P_ID));
    bool pickedUp;
    propData[1].at(P_PICKED_UP) == "1" ? pickedUp = true : pickedUp = false;
    int homeRoom = stoi(propData[1].at(P_HOME_ROOM));
    int solutionRoom = stoi(propData[1].at(P_SOLUTION_ROOM));
    int solutionProp = stoi(propData[1].at(P_SOLUTION_PROP));
    int blockingRoom = stoi(propData[1].at(P_BLOCKING_ROOM));
    int blockingProp = stoi(propData[1].at(P_BLOCKING_PROP));

    // pull out all the values into an object
    temp = new Prop(id, propData[1].at(P_NAME), pickedUp, homeRoom,
                    solutionRoom, solutionProp, blockingRoom,
                    blockingProp, commands, propData[1].at(P_LOOK_DESCRIPTION),
                    propData[1].at(P_USE_DESCRIPTION), propData[1].at(P_BLOCKER_TEXT), propData[1].at(P_SUCCESS_TEXT),
                    propData[1].at(P_TALK_TEXT));

    temp->print();

    // DEBUG: Print vector
    // for (unsigned long int index = 0; index < commands->size(); index++)
    // {
    //     std::cout << commands->at(index) << std::endl;
    // }
    // std::cout << "\n";

    // DEBUG: Print values in map
    // for (auto &elem : propData)
    // {
    //     std::cout << "Key: " << elem.first << " : ";
    //     std::cout << "Value: ";
    //     for (auto &elem1 : elem.second)
    //     {
    //         std::cout << elem1 << " | ";
    //     }
    //     std::cout << std::endl;
    // }

    // Next steps:

    // LOOP TO POPULATE OBJECTS START HERE

    // propData[1].at(P_BLOCKING_PROP)

    //
    // int id;
    // std::string name;                // name of prop
    // bool pickedUp;                   // whether or not item has been picked up by player. Used so player can't pick up items twice
    // int homeRoom;                    // the ID of the item's original location. Used for changing game state in other rooms.
    // int solutionRoom;                // ID of room where prop is meant to be used with SOLVE command
    // int solutionProp;                // If this prop is a KEY, solutionProp is the LOCk this KEY will unlock
    // int blockingRoom;                // If this prop blocks a room, this is ID of room blocked
    // std::vector<int> *validCommands; // This is a list of acceptable commands for this specific item. represented by an enum in main
    // std::string lookDescription;     // String returned when player uses LOOK command
    // std::string useDescription;      // String returned when player successfully USES this prop
    // std::string blockerText;         // If this prop is a blocker, this will be returned when they attempt to move past without first SOLVING
    // std::string successText;         // String returned when player successfully SOLVES with this prop
    // std::string talkText;            // String returned when player uses TALK command
    // bool expired;                    // Determines whether or not prop has been used to its fullest extent

    // TODO Parse valid commands, place in vector

    // // pull out all the values into an object
    // temp = new Prop(propData[1].at(P_ID), propData[1].at(P_NAME), propData[1].at(P_PICKED_UP), propData[1].at(P_HOME_ROOM),
    //                 propData[1].at(P_SOLUTION_ROOM), propData[1].at(P_SOLUTION_PROP), propData[1].at(P_BLOCKING_ROOM),
    //                 propData[1].at(P_BLOCKING_PROP), commands, propData[1].at(P_LOOK_DESCRIPTION),
    //                 propData[1].at(P_USE_DESCRIPTION), propData[1].at(P_BLOCKER_TEXT), propData[1].at(P_SUCCESS_TEXT),
    //                 propData[1].at(P_TALK_TEXT));

    // temp->print();

    // LOOP TO

    // Create another map where key is COMMAND_NAME, value is ENUM value of command
    // search the box with the commands in it, and load up the int values into this
    // prop's validCommands vector<int>
}

// Import props file into memory
void Database::importRooms()
{
    std::filesystem::path propsPath(createDBPath("rooms-test.csv"));
    std::string contents = readFileIntoString(propsPath);
    std::cout << contents;
}

void Database::import()
{
}

// Return prop given id
Prop *Database::getProp(const int &id) const
{
    Prop *temp = nullptr;

    for (unsigned long int index = 0; index < props->size(); index++)
    {
        if (props->at(index).getID() == id)
        {
            temp = &props->at(index);
            return temp;
        }
    }

    std::cout << "ERROR: PROP NOT FOUND";
    return temp;
}

// Returns a room given id
Room *Database::getRoom(const int &id) const
{
    Room *temp = nullptr;

    for (unsigned long int index = 0; index < rooms->size(); index++)
    {
        if (rooms->at(index).getID() == id)
        {
            return temp = &rooms->at(index);
        }
    }

    std::cout << "ERROR: ROOM NOT FOUND";
    return temp;
}

// Retrieves prop name by id
std::string Database::getPropName(const int &id) const
{
    for (unsigned long int index = 0; index < props->size(); index++)
    {
        if (props->at(index).getID() == id)
        {
            return props->at(index).getName();
        }
    }

    return "ERROR: PROP NAME NOT FOUND";
}

// Returns room name given id
std::string Database::getRoomName(const int &id) const
{
    for (unsigned long int index = 0; index < rooms->size(); index++)
    {
        if (rooms->at(index).getID() == id)
        {
            return rooms->at(index).getName();
        }
    }

    return "ERROR: ROOM NAME NOT FOUND";
}

// Returns a pointer to all the rooms
std::vector<Room> *Database::getRooms() const
{
    return rooms;
}

// Returns pointer to all the props
std::vector<Prop> *Database::getProps() const
{
    return props;
}
