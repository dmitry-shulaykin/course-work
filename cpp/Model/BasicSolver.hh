//
// Created by dima on 09.06.18.
//

#ifndef PROJECT_BASICSOLVER_HH
#define PROJECT_BASICSOLVER_HH


#include "Board.hh"
#include "AbstractSolver.hh"

template<class T>
class BasicSolver : public AbstractSolver<T> {

    using AbstractSolver<T>::m_score_function;
    std::unordered_set<uint64_t> used;

    static const int max_level = 19;
    std::vector<GameMove> moves;

protected:
    int dfs_search(Board &board, GameMove last_move, int depth) {
        if (depth == max_level) {
            return m_score_function(board);
        } else {
            constexpr std::pair<GameMove, GameMove> moves[4] = {
                    {GameMove::UP,    GameMove::DOWN},
                    {GameMove::DOWN,  GameMove::UP},
                    {GameMove::RIGHT, GameMove::LEFT},
                    {GameMove::LEFT,  GameMove::RIGHT}
            };

            int min_score = m_score_function(board), current_score = 0;
            for (auto &&move: moves) {
                if (last_move != move.second && board.isLegal(move.first)) {
                    board.applyMove(move.first);
                    current_score = dfs_search(board, move.first, depth + 1);
                    if (current_score < min_score)
                        min_score = current_score;
                    board.applyMove(move.second);
                }
            }
            return min_score;
        }
    }

public:
    std::vector<GameMove> solve(Board &board) override {
        moves.clear();
        Board sample_board = board;
        used.insert(sample_board.to_long_int());

        int score = 1000;
        while (!sample_board.checkWin()) {
            int score = 1000;
            GameMove best;
            bool best_set = false;
            for (int i = 1; i < 4; i++) {
                auto current_move = (GameMove) i;
                if (sample_board.isLegal(current_move)) {
                    Board copy_board = sample_board;
                    copy_board.applyMove(current_move);
                    int current_score = dfs_search(copy_board, current_move, 0);
                    std::cout << i << " score = " << current_score << std::endl;
                    if(!best_set){
                        best_set = true;
                        best = current_move;
                    }
                    if (current_score <= score && used.find(copy_board.to_long_int()) == used.end()) {
                        score = current_score;
                        best = current_move;
                    }
                }
            }

            if (sample_board.isLegal(best)) {
                sample_board.__debug();
                sample_board.applyMove(best);
                moves.push_back(best);
                used.insert(sample_board.to_long_int());
                std::cout << "runnin' OK" << std::endl;
            }else{
                std::cout << "fuck you"<< std::endl;
            }

        }
        return moves;
    };
};


#endif //PROJECT_BASICSOLVER_HH
