#include <iostream>
#include "../game.h"
#include "view.h"
#include <algorithm>

std::vector <GameMove> nextMoves;
constexpr int w=4, h=4, MAX_LEVEL = 19;
int calcScore(Game <w, h> *game) {
    int score = 0;

    auto getStart = [&w, &h](char c, int &x, int &y){
        if(c != '*'){
            int cc = c - 1;
            y = (int) (cc/w);
            x = (int) (cc%h);
        }else{
            x = (int) w-1;
            y = (int) h-1;
        }
    };

    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            int desire_x, desire_y;
            getStart(game->getData(j, i), desire_x, desire_y);

            int delta_x = abs(i - desire_y);
            int delta_y = abs(j - desire_x);
            score += (delta_x+delta_y);
            if(!delta_x && !delta_y){
                score-= 5*(1<<(w*h-i));
            }
        }
    }
    return score;
}

int solve_dfs(Game<w, h>* game,
                             int depth, GameMove last,
                             std::vector <GameMove> & move){

    GameMove best = GameMove::NOPE;

    if(depth == MAX_LEVEL){
        int score = calcScore(game);
        //debugScore(depth, score);
        return score;
    }else {
        int min_score = calcScore(game), current_score = 0;
        std::vector <GameMove> passup, passdown, passright, passleft;

        GameMove current_move;

        if(last != GameMove::DOWN && game->getFreeY() != h - 1) {
            game->applyMove(GameMove::UP);
            current_score = solve_dfs(game, depth + 1, GameMove::UP, passup);
            if (current_score < min_score) {
                best = GameMove::UP;
                min_score = current_score;
            }
            game->applyMove(GameMove::DOWN);
        }
        if(last != GameMove::UP && game->getFreeY() != 0) {
            game->applyMove(GameMove::DOWN);
            current_score = solve_dfs(game, depth+1, GameMove::DOWN, passdown);
            if(current_score < min_score){
                best = GameMove::DOWN;
                min_score = current_score;
            }
            game->applyMove(GameMove::UP);
        }

        if(last != GameMove::RIGHT && game->getFreeX() != w - 1) {
            game->applyMove(GameMove::LEFT);
            current_score = solve_dfs(game, depth+1, GameMove::LEFT, passleft);
            if(current_score < min_score){
                best = GameMove::LEFT;
                min_score = current_score;
            }
            game->applyMove(GameMove::RIGHT);
        }

        if(last != GameMove::LEFT && game->getFreeX() != 0) {
            game->applyMove(GameMove::RIGHT);
            current_score = solve_dfs(game, depth+1, GameMove::RIGHT, passright);
            if(current_score < min_score){
                best = GameMove::RIGHT;
                min_score = current_score;
            }
            game->applyMove(GameMove::LEFT);
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

GameMove getNextMove(Game<4,4>* game) {
    Game<4,4> * solver = new Game<4, 4>(*game);

    while(nextMoves.empty()){
        solve_dfs(solver, 0, GameMove::NOPE, nextMoves);
        if(nextMoves.empty()){
            int num_moves = 5;
            std::mt19937 generator;
            generator.seed(time(0));
            std::uniform_int_distribution<int> distribution(1,4);

            GameMove move;
            while(num_moves--) {
                move = (GameMove) distribution(generator);
                while(!solver->isLegal(move)) move = (GameMove) distribution(generator);
                solver->applyMove(move);
                nextMoves.push_back(move);
            }

            std::reverse(nextMoves.begin(), nextMoves.end());
        }
    }

    GameMove next = nextMoves.back();
    nextMoves.pop_back();
    return next;
}

int main(){
    auto game = new Game<4,4>();
    game->randomize(451, 100);

    int hod = 0;
    std::cout<<"hod = "<<hod<<std::endl;


    GameMove lastmove = GameMove::NOPE;
    while(true){
        View<4,4>::display(*game);
        GameMove move = getNextMove(game);
        game->applyMove(move);

        if(game->checkWin()){
            printf("Congrats u re winner! Totol %d moves.\n", game->getMoveCounter());
            break;
        }
    }
    return 0;

}