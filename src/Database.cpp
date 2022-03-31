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

// Import props file into memory
void Database::importProps()
{
    std::filesystem::path propsPath(createDBPath("props-test.csv"));
    std::string contents = readFileIntoString(propsPath);
    std::cout << contents;
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
