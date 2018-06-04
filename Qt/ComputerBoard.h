#ifndef PROJECT_COMPUTERBOARD_H
#define PROJECT_COMPUTERBOARD_H

#include "PlayerBoard.h"
#include "../Model/Board.hh"
#include "../Model/AbstractSolver.hh"

#include <vector>

class ComputerBoard: public PlayerBoard {

    std::vector<GameMove> moves;
    std::thread worker;

public:
    ComputerBoard(int player_id, const Board &game, bool enableInput = false,
                         QWidget *parent = nullptr);

    GameMove getNextMove();
    ~ComputerBoard() override;
public slots:
    void handleCanMove(GameMove) override;
};


#endif //PROJECT_COMPUTERBOARD_H
