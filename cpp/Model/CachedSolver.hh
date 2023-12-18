//
// Created by dima on 29.05.18.
//

#ifndef PROJECT_CACHEDSOLVER_HH
#define PROJECT_CACHEDSOLVER_HH

#include "AbstractSolver.hh"
template <class T>
class CachedSolver : public AbstractSolver<T>{
    using AbstractSolver<T>::m_score_function;

    int max_level = 15;
    std::vector<GameMove> nextMoves;
    double solve_dfs(Board &board, int depth, GameMove last, std::vector<GameMove> &move) {
        if (depth == max_level) {
            return (m_score_function)(board);
        } else {
            GameMove best = GameMove::NOPE;
            int min_score = (m_score_function)(board);
            int current_score = 10;
            std::vector<GameMove> passup, passdown, passright, passleft;


            if (last != GameMove::DOWN && board.isLegal(GameMove::UP)) {
                board.applyMove(GameMove::UP);
                current_score = solve_dfs(board, depth + 1, GameMove::UP, passup);
                if (current_score < min_score) {
                    best = GameMove::UP;
                    min_score = current_score;
                }
                board.applyMove(GameMove::DOWN);
            }
            if (last != GameMove::UP && board.isLegal(GameMove::DOWN)) {
                board.applyMove(GameMove::DOWN);
                current_score = solve_dfs(board, depth + 1, GameMove::DOWN, passdown);
                if (current_score < min_score) {
                    best = GameMove::DOWN;
                    min_score = current_score;
                }
                board.applyMove(GameMove::UP);
            }

            if (last != GameMove::RIGHT && board.isLegal(GameMove::LEFT)) {
                board.applyMove(GameMove::LEFT);
                current_score = solve_dfs(board, depth + 1, GameMove::LEFT, passleft);
                if (current_score < min_score) {
                    best = GameMove::LEFT;
                    min_score = current_score;
                }
                board.applyMove(GameMove::RIGHT);
            }

            if (last != GameMove::LEFT && board.isLegal(GameMove::RIGHT)) {
                board.applyMove(GameMove::RIGHT);
                current_score = solve_dfs(board, depth + 1, GameMove::RIGHT, passright);
                if (current_score < min_score) {
                    best = GameMove::RIGHT;
                    min_score = current_score;
                }
                board.applyMove(GameMove::LEFT);
            }

            switch (best) {
                case GameMove::UP:
                    move.insert(move.end(), passup.begin(), passup.end());
                    move.push_back(best);
                    break;
                case GameMove::DOWN:
                    move.insert(move.end(), passdown.begin(), passdown.end());
                    move.push_back(best);
                    break;
                case GameMove::LEFT:
                    move.insert(move.end(), passleft.begin(), passleft.end());
                    move.push_back(best);
                    break;
                case GameMove::RIGHT:
                    move.insert(move.end(), passright.begin(), passright.end());
                    move.push_back(best);
                    break;
                default:
                    break;
            }

            return min_score;
        }
    }

    GameMove getNextMove(Board &board) {
        Board solver = board;
        while (nextMoves.empty()) {
            solve_dfs(solver, 0, GameMove::NOPE, nextMoves);

            if (nextMoves.empty()) {
                int num_moves = 10;
                std::mt19937 generator;
                generator.seed((unsigned long) time(0));
                std::uniform_int_distribution<int> distribution(1, 4);

                GameMove move;
                while (num_moves--) {
                    move = (GameMove) distribution(generator);
                    while (!solver.isLegal(move)) move = (GameMove) distribution(generator);
                    solver.applyMove(move);
                    nextMoves.push_back(move);
                }
                reverse(nextMoves.begin(), nextMoves.end());
            }
        }
        GameMove next = nextMoves.back();
        nextMoves.pop_back();
        return next;
    }

    std::vector<GameMove> solve(Board &board) override {
        Board sample = board;
        std::vector<GameMove> moves;
        while (!sample.checkWin()) {
            moves.push_back(getNextMove(sample));
            sample.applyMove(moves.back());
        }
        return moves;
    }

public:
    explicit CachedSolver() : AbstractSolver<T>() {}
};

#endif //PROJECT_CACHEDSOLVER_HH
