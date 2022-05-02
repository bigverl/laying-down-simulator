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
        {"SOLVE", SOLVE},
        {"HELP", HELP},
        {"QUIT", QUIT},
        {"INVENTORY", INVENTORY}};

    _actions = new std::vector<std::string>{
        "USE",
        "LOOK",
        "GET",
        "PUSH",
        "PULL",
        "TALK",
        "OPEN",
        "CLOSE",
        "SOLVE",
        "HELP",
        "QUIT",
        "INVENTORY"};
}

void Database::initializeDirectionProcessor()
{
    directionProcessor = {
        {"NORTH", N},
        {"WEST", W},
        {"SOUTH", S},
        {"EAST", E}};

    _directions = new std::vector<std::string>{"NORTH", "WEST", "SOUTH", "EAST"};
}

int Database::parseDirection(const std::string &toParse)
{
    std::string temp = toParse;
    std::map<std::string, int>::iterator it;

    // ToUpper the action
    for (auto &c : temp)
    {
        c = (char)toupper(c);
    }

    // Find it
    it = directionProcessor.find(temp);

    // Return int
    if (it == directionProcessor.end())
    {
        return -1;
    }

    return it->second;
}

// Initializes direction processing tool
void Database::initializeAdjacencyProcessor()
{
    adjacencyProcessor = {
        {"N", N},
        {"W", W},
        {"S", S},
        {"E", E}};
}

// Parses a direction passed as string to int value to be used in enum
int Database::parseAdjacency(const std::string &toParse)
{
    std::string temp = toParse;
    std::map<std::string, int>::iterator it;

    // ToUpper the action
    for (auto &c : temp)
    {
        c = (char)toupper(c);
    }

    // Find it
    it = adjacencyProcessor.find(temp);

    // Return int
    if (it == adjacencyProcessor.end())
    {
        return -1;
    }

    return it->second;
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
    Prop *prop = nullptr;                               // temp item to populate

    // Import raw csv data to string, store in stream for processing
    std::filesystem::path propsPath(createDBPath("props.csv"));
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

        // Pull out all the values into an object
        prop = new Prop(id,
                        propData[mapIndex].at(P_NAME),
                        pickedUp,
                        homeRoom,
                        solutionRoom,
                        solutionProp,
                        blockingRoom,
                        blockingProp,
                        actionsFinal,
                        propData[mapIndex].at(P_LOOK_DESCRIPTION),
                        propData[mapIndex].at(P_USE_DESCRIPTION),
                        propData[mapIndex].at(P_BLOCKER_TEXT),
                        propData[mapIndex].at(P_SUCCESS_TEXT),
                        propData[mapIndex].at(P_TALK_TEXT));

        // DEBUG: Print the prop
        // prop->print();

        // Place prop into props array
        props->push_back(*prop);
    }

    // // // DEBUG: Print the entire props array
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
    delete prop;

    std::cout << "Props imported successfully" << std::endl;
}

// Import props file into memory
void Database::importRooms()
{
    // Declaration
    std::map<int, std::vector<std::string>> roomData;   // This holds each row of csv separately
    char delimiter = '|';                               // Delimeter for parsing csv cells
    std::vector<std::string> separatedRowData;          // Entire row of data
    std::string rawRowData;                             // Raw data from row
    std::vector<std::string> *propsData;                // Props in the room as string
    std::vector<int> *props;                            // Props in the room as string
    std::vector<std::string> *adjacencyData = nullptr;  // Holds adjacencies for processing
    std::vector<AdjacentRoom> *adjacentRooms = nullptr; // Adjacent rooms for one room
    AdjacentRoom *singleAdjacency = nullptr;            // single adjacency to insert into adjacency list
    int roomID;                                         // Adjacent room ID to populate adjacentroom object
    int direction;                                      // Adjacent room direction to populate adjacentroom object
    Room *room = nullptr;                               // Temp room to populate

    // Code start
    rooms = new std::vector<Room>; // Create rooms array

    // Import raw csv data to string, store in stream for processing
    std::filesystem::path roomsPath(createDBPath("rooms.csv"));
    std::string fileContents = readFileIntoString(roomsPath);
    std::istringstream sstream(fileContents);

    // // Pull each row of data from stream and insert into map
    int counter = 0;
    while (std::getline(sstream, rawRowData))
    {
        std::istringstream line(rawRowData);
        while (std::getline(line, rawRowData, delimiter))
        {
            separatedRowData.push_back(rawRowData);
        }

        roomData[counter] = separatedRowData;
        separatedRowData.clear();
        counter++;
    }

    // DEBUG: Print values in map
    // for (auto &elem : roomData)
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
    // Populate rooms
    for (unsigned long int mapIndex = 1; mapIndex < roomData.size(); mapIndex++)
    {
        // Pull out individual props from prop cell, and convert to ints
        propsData = split(roomData[mapIndex].at(R_PROPS));
        props = new std::vector<int>;
        for (unsigned long int index = 0; index < propsData->size(); index++)
        {
            props->push_back(stoi(propsData->at(index)));
        }

        // Pull individually-grouped adjacentRoom entries from cell (use 0 and 2 because it's "1-e")

        adjacencyData = split(roomData[mapIndex].at(R_ADJACENT_CELLS));
        adjacentRooms = new std::vector<AdjacentRoom>;
        // Do the pull
        for (unsigned long int index = 0; index < adjacencyData->size(); index++)
        {
            // If the contents of the adjacency is > 2 then it has a roomID and a direction
            if (adjacencyData->at(index).size() > 2)
            {
                roomID = stoi(adjacencyData->at(index).substr(0, 1));
                direction = parseAdjacency(adjacencyData->at(index).substr(2, 1));
                singleAdjacency = new AdjacentRoom(roomID, direction);
                adjacentRooms->push_back(*singleAdjacency);
            }
            else
            {
                singleAdjacency = new AdjacentRoom(-1, -1);
                adjacentRooms->push_back(*singleAdjacency);
            }
        }

        // Convert all database attributes to appropriate data structures for object construction
        // Attributes
        int id = stoi(roomData[mapIndex].at(R_ID));
        std::string name = roomData[mapIndex].at(R_NAME);
        std::string descriptionTextDefault = roomData[mapIndex].at(R_DESCRIPTION_TEXT_DEFAULT);
        std::string descriptionTextSolved = roomData[mapIndex].at(R_DESCRIPTION_TEXT_SOLVED);
        std::string descriptionPic = roomData[mapIndex].at(R_DESCRIPTION_PIC);

        // Pull out all the values into an object
        room = new Room(id,
                        name,
                        props,
                        adjacentRooms,
                        descriptionTextDefault,
                        descriptionTextSolved,
                        descriptionPic);
        rooms->push_back(*room);
    }

    // // DEBUG:
    // // Print the entire rooms array :
    // for (unsigned long int index = 0; index < rooms->size(); index++)
    // {
    //     std::cout << std::endl;
    //     std::cout << std::endl;
    //     std::cout << "------------ Printing room #" << index + 1 << " ---------- " << std::endl;
    //     rooms->at(index).print();
    // }

    // Delete pointers
    delete propsData;
    delete props;
    delete adjacencyData;
    delete adjacentRooms;
    delete singleAdjacency;
    delete room;

    std::cout << "Rooms imported successfully" << std::endl;
}

void Database::import()
{
    importProps();
    importRooms();
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

// Get directions vector
std::vector<std::string> *Database::getDirections()
{
    return _directions;
}

// Get actions vector
std::vector<std::string> *Database::getActions()
{
    return _actions;
}

// Get roomnames vector
std::vector<std::string> *Database::getRoomNames()
{
    return _roomNames;
}

// Player will reference props by name, and so we must retrieve their ID's by name
int Database::getPropIDByName(std::string name)
{
    for (unsigned long int index = 0; index < props->size(); index++)
    {
        // ToLower the prop name. This is a workaround
        for (auto &c : name)
        {
            c = (char)tolower(c);
        }

        // ToUpper
        if (props->at(index).getName() == name)
        {
            return props->at(index).getID();
        }
    }

    return -1;
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

// Gets prop in origin that blocks destination. Returns -1 if nothing blocking
int Database::getRoomBlockerID(const int &origin, const int &destination)
{
    // Get the props in this room
    std::vector<int> *propsInRoom = getRooms()->at(origin).getProps();
    bool found = false;
    unsigned long int index = 0;
    int blockingPropID = -1;
    int blockedRoom = -1;

    // Don't check if no props
    int noProps = getRooms()->at(origin).getProps()->at(index);
    if (noProps != -1)
    {
        // Get the one that's blocking the given room ID
        while (!found && index < propsInRoom->size())
        {
            blockedRoom = getProps()->at(propsInRoom->at(index)).getBlockingRoom();
            found = (destination == blockedRoom);

            if (found)
            {
                blockingPropID = getProps()->at(propsInRoom->at(index)).getID();
            }

            index++;
        }
    }

    // Return its ID
    return blockingPropID;
}

// Returns prop blocking this one. Returns -1 if prop is not blocked or if the blocker is exhausted
int Database::getPropBlockerID(const int &propID)
{
    int blockerID = -1;
    bool found = false;
    unsigned long int index = 0;

    while (!found && index < DB.getProps()->size())
    {
        // if found, and the found prop is not expire, register it
        found = (propID == DB.getProps()->at(index).getBlockingPropID());
        if (found && (!DB.getProps()->at(index).isExpired()))
        {
            blockerID = DB.getProps()->at(index).getID();
        }
        else
        {
            index++;
        }
    }

    return blockerID;
    // return that value
}

// Debug: Returns ID for room adjacent to room ID and direction given. Returns -1 if invalid
int Database::getAdjacentRoomID(const int &origin, const int &direction)
{
    // search origin room's adjacencies, return the one in given direction
    std::vector<AdjacentRoom> *tempAdjacencies = getRooms()->at(origin).getAdjacentRooms();
    unsigned long int index = 0;
    bool found = false;
    int adjacentRoomID = -1;

    while (!found && index < tempAdjacencies->size())
    {
        found = (direction == tempAdjacencies->at(index)._direction);

        if (found)
        {
            adjacentRoomID = tempAdjacencies->at(index)._roomID;
        }

        index++;
    }

    return adjacentRoomID;
}

// Creates room descriptions and allocates them to room objects
void Database::initializeRoomDescriptions()
{
    auto ss = std::ostringstream{};
    std::string desc = "";
    _roomNames = new std::vector<std::string>{
        "Your Bedroom",
        "The Kitchen",
        "A Dark Scary Tunnel",
        "Secret Tunnels (Hub)",
        "Secret Tunnels (North)",
        "Secret Tunnels (South)",
        "Secret Tunnels (East)",
        "Your Classroom"};

    ss << "This is your bedroom. It’s kind of small and there’s only room for a full-sized bed, a bedside\n"
       << "table, and a dresser. You haven’t had much time to clean it since you’ve been bombarded with\n"
       << "projects and midterms just before spring break. On the floor is a pile of CLOTHES that have\n"
       << "been sitting there for a while. On top of your bedside table, there’s an alarm clock, lamp, your\n"
       << "KEYS, and some miscellaneous junk. On your dresser is a bunch of collectible figurines from \n"
       << "various video games. You should really get around to cleaning this mess.\n";
    desc = ss.str();
    rooms->at(0).setDescriptionTextDefault(desc);
    ss.str("");

    ss << "This is your shared kitchen. There’s a sink full of dishes your roommate never washed, cabinets,\n"
       << "and a fridge. On the counter is your beloved pet fish. The fish is swimming around in the tank that\n"
       << "you managed to put together. The cabinets are full of both healthy and unhealthy snacks,\n"
       << "spices, cups, and dishes. The fridge is barely stocked and full of leftovers. There’s a bunch of\n"
       << "energy drinks lined up along the fridge door along with some condiments. On top of the fridge is\n"
       << "some fish FOOD. Across the kitchen is your banged up front DOOR. It seems like a lot of things\n"
       << "in this apartment need some work.\n";
    desc = ss.str();
    rooms->at(1).setDescriptionTextDefault(desc);
    ss.str("");

    ss << "You decide to take a shortcut through the tunnels connecting your dorm room to the CS building.\n"
       << "You don't remember it being this spooky or dark down here. After a moment, you catch a glimpse\n"
       << "of what seems to be a pile of bones in the darkness. As your eyes adjust, you notice a FLASHLIGHT\n"
       << "lying near the skeleton. That’s not a good sign. You hope that won't be your fate as well.\n";
    desc = ss.str();
    rooms->at(2).setDescriptionTextDefault(desc);
    ss.str("");

    ss << "Now flooded with light, you can now see your surroundings. You look around and spot some sort\n"
       << "of MACHINE sitting lifelessly. It looks old and beat up, like it hasn’t been used in a long\n"
       << "time. You wonder how it ended up down here and what it was once used for. There seem to be\n"
       << "other tunnels branching out from every direction. Near the east is a sign that reads:\n"
       << "\"SHORTCUT TO CS BUILDING THIS WAY ---->\"\n";
    desc = ss.str();
    rooms->at(3).setDescriptionTextDefault(desc);
    ss.str("");

    ss << "You decide to travel to the north tunnel. You instantly get startled by a GHOST, but after some\n"
       << "observation it seems to be harmless. The GHOST seems too focused on their task at hand to\n"
       << "notice you. Next to the GHOST is a weird lump of MEAT. It seems like it’s been sitting there\n"
       << "for a while. Gross.\n";
    desc = ss.str();
    rooms->at(4).setDescriptionTextDefault(desc);
    ss.str("");

    ss << "You decide to travel to the south tunnel. There is a scary-looking DOG blocking your way. It\n"
       << "looks like it hasn't had a meal since the last time the administration had to deal with the\n"
       << "adjunct faculty demanding a living wage. It also seems particularly protective of a large\n"
       << "ROCK near the back of the cavern.\n";
    desc = ss.str();
    rooms->at(5).setDescriptionTextDefault(desc);
    ss.str("");

    ss << "You excitedly head through the eastern tunnel only to find that there's been a cave-in.\n"
       << "Investigating the debris, you remember that the university has recently demolished part of\n"
       << "the CS building to install another Starbucks on campus. You seem to recall the Deputy Assistant\n"
       << "to the Vice Provost of Student Capital Relations ensuring the students that the decrease in\n"
       << "classrooms would only increase class sizes by 28.6%, which was well within the parameters of \n"
       << "the school's mission statement. Regardless, it looks like you're going to need to find another\n"
       << "way to get to class.\n";
    desc = ss.str();
    rooms->at(6).setDescriptionTextDefault(desc);
    ss.str("");

    ss << "You shriek through time and space for what seems like an eternity until the portal spits you out\n"
       << "near the back of a classroom. You feel lucky to have survived! Equally fortuitous is that no one\n"
       << "noticed the tear in the void because everyone's too busy bragging about many hours they've clocked\n"
       << "in Elden Ring instead of studying for the midterm. You hear a few announcements of \"D's get degrees\"\n"
       << "as the portal closes.\n"
       << "\n"
       << "It seems that not only have you arrived in the correct classroom, but you're just in time!\n"
       << "You brush off the overwhelming feeling of existential dread and notice that your professor has just\n"
       << "started handing out exams. Scanning the room, you find a single empty left-handed DESK to sit in.\n"
       << "Better hurry, or you'll forget to put your name on the exam like last time!\n";
    desc = ss.str();
    rooms->at(7).setDescriptionTextDefault(desc);
    ss.str("");
}