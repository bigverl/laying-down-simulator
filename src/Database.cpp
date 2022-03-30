#include "Database.h"

Database &Database::getInstance()
{
    static Database instance;
    return instance;
}

// TODO make sure proper csv file type is added to the params list
void Database::import()
{
}

// TODO: Make sure this looks up and returns a prop by id. the placeholder Prop(); is just here to prevent
// compile errors rn
Prop Database::getProp(const int &id) const
{
    return Prop();
}

// TODO: Make sure this looks up and returns a room by id. the placeholder Prop(); is just here to prevent
// compile errors rn
Room Database::getRoom(const int &id) const
{
    return Room();
}

std::string Database::getPropName(const int &id) const
{
    return "";
}

std::string Database::getRoomName(const int &id) const
{
    return "";
}

std::vector<Room> *Database::getRooms() const
{
    return nullptr;
}
