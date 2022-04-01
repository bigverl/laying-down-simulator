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
    //  Declaration
    props = new std::vector<Prop>;                      // Create props array
    std::map<int, std::vector<std::string>> propData;   // This holds each row of csv separately
    char delimiter = '|';                               // Delimeter for parsing csv cells
    std::vector<std::string> separatedRowData;          // Entire row of data
    std::string rawRowData;                             // Raw data from row
    std::vector<std::string> *actionsToParse = nullptr; // Commands to place in valid commands vector
    std::vector<int> *actionsFinal = nullptr;           // Actual commands list to populate object
    Prop *temp = nullptr;                               // temp item to populate

    // Import raw csv data to string, store in stream for processing
    std::filesystem::path propsPath(createDBPath("props-test.csv"));
    std::string fileContents = readFileIntoString(propsPath);
    std::istringstream sstream(fileContents);

    // Pull each row of data from stream and insert into map
    int counter = 0;
    while (std::getline(sstream, rawRowData))
    {
        std::istringstream line(rawRowData);
        while (std::getline(line, rawRowData, delimiter))
        {
            separatedRowData.push_back(rawRowData);
        }

        propData[counter] = separatedRowData;
        separatedRowData.clear();
        counter++;
    }

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

    // NOTE: This needs to start at 1 because the database has headers so the first line is bunk
    // Populate props
    for (unsigned long int mapIndex = 1; mapIndex < propData.size(); mapIndex++)
    {
        // Pull individual actions from actions cell and place in actions vector
        actionsToParse = split(propData[mapIndex].at(P_VALID_COMMANDS));
        actionsFinal = new std::vector<int>;
        for (unsigned long int index = 0; index < actionsToParse->size(); index++)
        {
            actionsFinal->push_back(parseAction(actionsToParse->at(index)));
        }

        // Convert all database attributes to appropriate data structures for object construction
        int id = stoi(propData[mapIndex].at(P_ID));
        bool pickedUp;
        propData[mapIndex].at(P_PICKED_UP) == "1" ? pickedUp = true : pickedUp = false;
        int homeRoom = stoi(propData[mapIndex].at(P_HOME_ROOM));
        int solutionRoom = stoi(propData[mapIndex].at(P_SOLUTION_ROOM));
        int solutionProp = stoi(propData[mapIndex].at(P_SOLUTION_PROP));
        int blockingRoom = stoi(propData[mapIndex].at(P_BLOCKING_ROOM));
        int blockingProp = stoi(propData[mapIndex].at(P_BLOCKING_PROP));

        // pull out all the values into an object
        temp = new Prop(id, propData[mapIndex].at(P_NAME), pickedUp, homeRoom,
                        solutionRoom, solutionProp, blockingRoom,
                        blockingProp, actionsFinal, propData[mapIndex].at(P_LOOK_DESCRIPTION),
                        propData[mapIndex].at(P_USE_DESCRIPTION), propData[mapIndex].at(P_BLOCKER_TEXT), propData[mapIndex].at(P_SUCCESS_TEXT),
                        propData[mapIndex].at(P_TALK_TEXT));

        // DEBUG: Print the prop
        // temp->print();

        // Place prop into props array
        props->push_back(*temp);
    }

    // DEBUG: Print the entire props array:
    // for (unsigned long int index = 0; index < props->size(); index++)
    // {
    //     std::cout << std::endl;
    //     std::cout << std::endl;
    //     std::cout << "------------ Printing prop #" << index + 1 << " ---------- " << std::endl;
    //     props->at(index).print();
    // }

    // Delete pointers
    delete actionsFinal;
    delete actionsToParse;
    delete temp;
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
