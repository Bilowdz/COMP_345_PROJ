//
// Created by Nicolo pt 2 on 2021-11-07.
//

#ifndef CMAKELISTS_TXT_STATE_H
#define CMAKELISTS_TXT_STATE_H


enum State
{
    ST_START,
    ST_MAP_LOADED,
    ST_MAP_VALIDATED,
    ST_PLAYERS_ADDED,
    ST_ASSIGN_REINFORCEMENT,
    ST_ISSUE_ORDERS,
    ST_EXECUTE_ORDERS,
    ST_WIN,
    ST_END,
    ST_ERROR
};

static const char *enum_state_str[] =
        { "Start", "Map Loaded", "Map Validated","Players Added","Assign Reinforcement","Issue Orders","Execute Orders","Win"};

#endif //CMAKELISTS_TXT_STATE_H