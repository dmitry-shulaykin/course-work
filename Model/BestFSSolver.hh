//
// Created by dima on 29.05.18.
//

#ifndef PROJECT_ASTARSOLVER_HH
#define PROJECT_ASTARSOLVER_HH

#include "AbstractSolver.hh"

class BestFSSolver: public AbstractSolver{
    static constexpr int MAX_LEVEL = 150;

    std::vector <GameMove> Astar_search(Board &board){
        constexpr std::pair<GameMove, GameMove> opp_moves[4] = {

                {GameMove::UP, GameMove::DOWN},
                {GameMove::DOWN, GameMove::UP},
                {GameMove::RIGHT, GameMove::LEFT},
                {GameMove::LEFT, GameMove::RIGHT}
        };

        std::map <__uint128_t, GameMove> closed_set;
        std::set < std::pair <std::pair <int, int>, __uint128_t> > open_set;
        __uint128_t packed = board.to_long_int(), final;
        //SimpleScoreFunctor f;
        open_set.insert({{(*m_score_function)(board), 0}, board.to_long_int()});
        closed_set.insert({packed, GameMove::NOPE});
        while(!open_set.empty()){
            auto top_it = open_set.begin();
            auto current = *top_it;

            open_set.erase(top_it);
            Board current_board;


            current_board.load_from_long(current.second);
            if(current_board.checkWin()){
                std::cout<<"Found a win"<<std::endl;
                std::cout<<"Moves: "<<current.first.second<<std::endl;
                std::cout<<"Board: "<<std::endl;
                current_board.__debug();
                final = current_board.to_long_int();
                std::cout<<current_board.checkWin()<<std::endl;
                break;
            }else{

                for(auto &&move: opp_moves){
                    if(current_board.isLegal(move.first)) {
                        current_board.applyMove(move.first);
                        if(closed_set.find(current_board.to_long_int()) == closed_set.end() && current.first.second < MAX_LEVEL){
                            open_set.insert({
                                     {
                                             (*m_score_function)(current_board),
                                         current.first.second+1
                                     },
                                     current_board.to_long_int()
                            });
                            closed_set.insert({current_board.to_long_int(), move.first});
                        }
                        current_board.applyMove(move.second);
                    }
                }
            }
        }

        std::vector <GameMove> moves;
        for(__uint128_t cboard = final; cboard != packed;){
            auto move = closed_set[cboard];
            Board b;
            b.load_from_long(cboard);
            b.applyMove(opp_moves[((int)move) - 1].second);
            moves.push_back(move);
            cboard = b.to_long_int();
        }
        //std::reverse(moves.begin(), moves.end());
        return moves;
    }

    std::vector <GameMove> solve(Board &board) override{
        Board sample = board;
        return Astar_search(sample);
    }
public:
    explicit BestFSSolver(std::shared_ptr<AbstractScoreFunctor> score_function):
            AbstractSolver(std::move(score_function)) {};

};


#endif //PROJECT_ASTARSOLVER_HH
