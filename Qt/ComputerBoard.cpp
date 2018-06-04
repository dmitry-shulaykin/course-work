//
// Created by dima on 18.03.18.
//

#include "ComputerBoard.h"
#include "../Model/BestFSSolver.hh"

ComputerBoard::ComputerBoard(int player_id, const Board &game, bool enableInput, QWidget *parent)
        : PlayerBoard(player_id, game, enableInput, true, parent),
          worker([&game, this]() {

              std::shared_ptr<AbstractScoreFunctor> score_func(new SimpleScoreFunctor());
              BestFSSolver solver(score_func);
              Board sample = game;
              moves = solver.solveWrap(sample);
          }) {

}

GameMove ComputerBoard::getNextMove() {
    if (worker.joinable()) {
        worker.join();
        std::cout << "moves: " << moves.size() << std::endl;
    }

    if (moves.size()) {
        GameMove move = moves.back();
        moves.pop_back();

        std::pair<int, int> offs[5];
        offs[(int)GameMove::NOPE] = {0, 0};
        offs[(int)GameMove::UP] = {0, +1};
        offs[(int)GameMove::DOWN] = {0, -1};
        offs[(int)GameMove::LEFT] = {+1, 0};
        offs[(int)GameMove::RIGHT] = {-1, 0};
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (buttons[i][j]->text() == " ") {
                    updateBoard(buttons[i][j], buttons[i + offs[(int) move].second][j + offs[(int) move].first]);
                    return move;
                }
            }
        }

    }

    return GameMove::NOPE;
}


void ComputerBoard::handleCanMove(GameMove m) {
   // renderGame();
    makeMove(getNextMove());
}

ComputerBoard::~ComputerBoard() {
    if (worker.joinable())
        worker.detach();
};

