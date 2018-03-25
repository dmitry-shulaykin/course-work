#ifndef PROJECT_COMPUTERBOARD_H
#define PROJECT_COMPUTERBOARD_H

#include "player-board.h"
#include "../game.h"

#include <vector>

class ComputerBoard: public PlayerBoard {

    std::vector<GameMove> nextMoves;

    int max_level = 16;

    int calcScore(Game <w, h> *game);

    int solve_dfs(Game<w, h>* game,
                   int depth, GameMove last,
                   std::vector <GameMove> & move);


public:
    ComputerBoard(int player_id, Game<w, h> * game, bool enableInput = false,
                         QWidget *parent = nullptr);

    GameMove getNextMove();

public slots:
    void handleCanMove(GameMove) override;
};


#endif //PROJECT_COMPUTERBOARD_H
