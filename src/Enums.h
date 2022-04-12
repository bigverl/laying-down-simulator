#ifndef ENUMS_H
#define ENUMS_H

// Column positions in props.csv database. Used by database to import and populate prop data
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

// Column positions in rooms.csv database. Used by database to import and populate room data
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

// Actions player can take. Used to parse player input into commands commands
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
    SOLVE,
    HELP,
    QUIT,
    INVENTORY
};

// Adjacencies to given room. Used by Database to import data to room objects
enum Adjacencies
{
    N,
    W,
    S,
    E,
};

// Enum outlining directions players may move. Used to interpret player movement commands
enum Directions
{
    NORTH,
    WEST,
    SOUTH,
    EAST,
};

// Enum representing command structure. Used to parse player input as commands
enum Command
{
    ACTION,
    ARG1,
    ARG2
};

#endif