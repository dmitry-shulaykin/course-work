#ifndef PROJECT_COMPUTERBOARD_H
#define PROJECT_COMPUTERBOARD_H

#include "player-board.h"
#include "../game.h"

#include <vector>

class ComputerBoard: public PlayerBoard {

    std::vector<GameMove> nextMoves;

    static constexpr int MAX_LEVEL = 18;

    static int calcScore(Game <w, h> *game);

    static int solve_dfs(Game<w, h>* game,
                   int depth, GameMove last,
                   std::vector <GameMove> & move);


public:
    ComputerBoard(int player_id, Game<w, h> * game, bool enableInput = false,
                         QWidget *parent = nullptr);

    GameMove getNextMove();

public slots:
    void makeMove(GameMove) override;

};


#endif //PROJECT_COMPUTERBOARD_H
