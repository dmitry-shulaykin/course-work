//
// Created by dima on 04.06.18.
//

#ifndef PROJECT_HELPBOARD_HH
#define PROJECT_HELPBOARD_HH

#include "PlayerBoard.h"

class HelpBoard : public PlayerBoard{
    HelpBoard(int player_id, const Board &game, bool enableInput = true, bool enableHelp = true, QWidget *parent = nullptr):
            PlayerBoard(player_id, game){

    }
};

#endif //PROJECT_HELPBOARD_HH
