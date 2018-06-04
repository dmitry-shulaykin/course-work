//
// Created by dima on 30.05.18.
//

#ifndef PROJECT_SEARCH_HH
#define PROJECT_SEARCH_HH

#include <set>
#include <functional>
#include <memory>

#include "../Model/Board.hh"
#include "../Model/ScoringFunctions.hh"


int search(const Board &board, const std::shared_ptr<AbstractScoreFunctor> &score){

    static constexpr int MAX_LEVEL = 130;
    std::set <__uint128_t> closed_set;
    std::set < std::pair <std::pair <double, int>, __uint128_t> > open_set;

    __uint128_t packed = board.to_long_int();
    open_set.insert({{(*score)(board), 0}, board.to_long_int()});

    while(!open_set.empty()){
        auto top_it = open_set.begin();
        auto current = *top_it;
        //std::cout<<open_set.size()<<std::endl;
        open_set.erase(top_it);
        Board current_board;
        if(closed_set.find(current.second) != closed_set.end()) continue;
        closed_set.insert(current.second);
        current_board.load_from_long(current.second);

        //std::cout<<"Current board: "<<calcScore(current_board)<<std::endl;
        //current_board.__debug();

        if(current_board.checkWin()){
            std::cout<<"Found a win"<<std::endl;
            std::cout<<"Moves: "<<current.first.second<<std::endl;
            std::cout<<"Board: "<<std::endl;
            current_board.__debug();
            std::cout<<current_board.checkWin()<<std::endl;
            return current.first.second;
        }else{
            constexpr std::pair<GameMove, GameMove> moves[4] = {
                    {GameMove::UP, GameMove::DOWN},
                    {GameMove::DOWN, GameMove::UP},
                    {GameMove::RIGHT, GameMove::LEFT},
                    {GameMove::LEFT, GameMove::RIGHT}
            };
            for(auto &&move: moves){
                if(current_board.isLegal(move.first)) {
                    current_board.applyMove(move.first);
                    if(closed_set.find(current_board.to_long_int()) == closed_set.end() && current.first.second < MAX_LEVEL){
                        open_set.insert({ {(*score)(current_board), current.first.second+1}, current_board.to_long_int() });
                    }
                    current_board.applyMove(move.second);
                }
            }
        }
    }
}



#endif //PROJECT_SEARCH_HH
