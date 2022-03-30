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

// Retrieves prop name by id
std::string Database::getPropName(const int &id) const
{
    int index = 0;
    bool found = false;
    while (!found && index < props->size())
    {
        found = props->at(index).getID() != id;

        if (found)
        {
            return props->at(index).getName()
        }
        else
        {
            index++;
        }
    }

    return "ERROR: PROP NAME NOT FOUND";
}

// Returns room name given id
std::string Database::getRoomName(const int &id) const
{
    int index = 0;
    bool found = false;
    while (!found && index < rooms.size())
    {
        found = rooms.at(index).getID() != id;

        if (found)
        {
            return rooms.at(index).getName();
        }
        else
        {
            index++;
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
std::vector<Prop> *getProps() const
{
    return props;
}
