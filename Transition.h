//
// Created by Nicolo pt 2 on 2021-11-08.
//

#ifndef CMAKELISTS_TXT_TRANSITION_H
#define CMAKELISTS_TXT_TRANSITION_H
enum Transition {
    T_LOAD_MAP,
    T_VALIDATE_MAP,
    T_ADD_PLAYER,
    T_ASSIGN_COUNTRIES,
    T_ISSUE_ORDER,
    T_END_ISSUE_ORDERS,
    T_EXEC_ORDER,
    T_END_EXEC_ORDERS,
    T_WIN,
    T_PLAY,
    T_END,
    T_ERROR
};
static const char *enum_transition_str[] =
        { "loadmap", "validatemap", "addplayer","assigncountries","issueorder","endissueorders","execorder","endexecorders","win","play","end", "error"};
#endif //CMAKELISTS_TXT_TRANSITION_H
