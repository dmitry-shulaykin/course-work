//
// Created by dima on 13.05.18.
//

#ifndef PROJECT_SOLVER_HH
#define PROJECT_SOLVER_HH

//
// Created by dima on 18.03.18.
//

#include <cmath>
#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>

#include "../Model/AbstractSolver.hh"

/*

class BasicSolver: public AbstractSolver{
    static const int max_level = 15;
    std::vector <GameMove> moves;
protected:
    static int dfs_search(Board &board, GameMove last_move, int depth){
        if(depth == max_level){
            return calcScore(board);
        }else{
            constexpr std::pair<GameMove, GameMove> moves[4] = {
                    {GameMove::UP, GameMove::DOWN},
                    {GameMove::DOWN, GameMove::UP},
                    {GameMove::RIGHT, GameMove::LEFT},
                    {GameMove::LEFT, GameMove::RIGHT}
            };

            int min_score = calcScore(board), current_score = 0;
            for(auto &&move: moves){
                if(last_move != move.second && board.isLegal(move.first)) {
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
    std::vector <GameMove> solve(Board &board) override{
        moves.clear();
        Board sample_board = board;
        GameMove best;
        int score = 0;
        while(!sample_board.checkWin()){
            for(int i = 1; i < 4; i++){
                auto current_move = (GameMove) i;
                if(sample_board.isLegal(current_move)){
                    Board copy_board = sample_board;
                    copy_board.applyMove(current_move);
                    int current_score = dfs_search(copy_board, current_move, 0);
                    if(current_score <= score){
                        score = current_score;
                        best = current_move;
                    }
                }
            }

            if(sample_board.isLegal(best)) {
                //sample_board.__debug();
               // std::cout<<(int)best<<std::endl;
                sample_board.applyMove(best);
                moves.push_back(best);
              //  std::cout<<"runnin' OK"<<std::endl;
            }

        }
        return moves;
    };
};



class CachedSolver : public AbstractSolver{
    int max_level = 15;
    std::vector<GameMove> nextMoves;
    static int calcScore(Board &board) {
        int score = 0;

        auto getStart = [&board](int c, int &x, int &y){
            if(c != 0){
                int cc = c - 1;
                y = cc/board.getWidth();
                x = cc%board.getHeight();
            }else{
                x = board.getWidth()-1;
                y = board.getHeight()-1;
            }
        };

        int w = board.getWidth(), h = board.getHeight();
        for(int i = 0; i < h; i++){
            for(int j = 0; j < w; j++){
                int desire_x, desire_y;
                getStart(board.getData(j, i), desire_x, desire_y);

                int delta_x = abs(i - desire_y);
                int delta_y = abs(j - desire_x);

                if(!delta_x && !delta_y){
                    score-= 1000;
                }else{
                    int seek = i*w + j + 1;
                    for(int k = 0; k < h; k++){
                        for(int q = 0; q < w; q++){
                            if(board.getData(q, k) == seek){
                                delta_x = abs(q-j);
                                delta_y = abs(k-i);
                                score += delta_x + delta_y;
                                return score;
                            }
                        }
                    }
                }
            }
        }
        return score;
    }

    int solve_dfs(Board &board, int depth, GameMove last, std::vector <GameMove> & move){
        if(depth == max_level){
            return calcScore(board);
        }else {
            GameMove best = GameMove::NOPE;
            int min_score = calcScore(board), current_score = 0;
            std::vector <GameMove> passup, passdown, passright, passleft;


            if(last != GameMove::DOWN && board.isLegal(GameMove::UP)) {
                board.applyMove(GameMove::UP);
                current_score = solve_dfs(board, depth + 1, GameMove::UP, passup);
                if (current_score < min_score) {
                    best = GameMove::UP;
                    min_score = current_score;
                }
                board.applyMove(GameMove::DOWN);
            }
            if(last != GameMove::UP && board.isLegal(GameMove::DOWN)) {
                board.applyMove(GameMove::DOWN);
                current_score = solve_dfs(board, depth+1, GameMove::DOWN, passdown);
                if(current_score < min_score){
                    best = GameMove::DOWN;
                    min_score = current_score;
                }
                board.applyMove(GameMove::UP);
            }

            if(last != GameMove::RIGHT && board.isLegal(GameMove::LEFT)) {
                board.applyMove(GameMove::LEFT);
                current_score = solve_dfs(board, depth+1, GameMove::LEFT, passleft);
                if(current_score < min_score){
                    best = GameMove::LEFT;
                    min_score = current_score;
                }
                board.applyMove(GameMove::RIGHT);
            }

            if(last != GameMove::LEFT && board.isLegal(GameMove::RIGHT)) {
                board.applyMove(GameMove::RIGHT);
                current_score = solve_dfs(board, depth+1, GameMove::RIGHT, passright);
                if(current_score < min_score){
                    best = GameMove::RIGHT;
                    min_score = current_score;
                }
                board.applyMove(GameMove::LEFT);
            }

            switch (best){
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
                default: break;
            }

            return min_score;
        }
    }

    GameMove getNextMove(Board &board) {
        Board solver = board;
        while(nextMoves.empty()){
            solve_dfs(solver, 0, GameMove::NOPE, nextMoves);

            if(nextMoves.empty()){
                int num_moves = 10;
                std::mt19937 generator;
                generator.seed((unsigned long)time(0));
                std::uniform_int_distribution<int> distribution(1,4);

                GameMove move;
                while(num_moves--) {
                    move = (GameMove) distribution(generator);
                    while(!solver.isLegal(move)) move = (GameMove) distribution(generator);
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
public:
    std::vector<GameMove> solve(Board &board) override {
        Board sample = board;
        std::vector <GameMove> moves;
        while(!sample.checkWin()){
            moves.push_back(getNextMove(sample));
            sample.applyMove(moves.back());
        }
        return moves;
    }

};

 */
#endif //PROJECT_SOLVER_HH
