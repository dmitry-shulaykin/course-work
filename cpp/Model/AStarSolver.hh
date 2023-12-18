//
// Created by dima on 29.05.18.
//

#ifndef PROJECT_ASTARSOLVER_HH
#define PROJECT_ASTARSOLVER_HH

#include <map>
#include <unordered_map>
#include "AbstractSolver.hh"
#include <queue>
template <class T>
class AStarSolver: public AbstractSolver<T>{

    // Функция оценки
    using AbstractSolver<T>::m_score_function;

    // Коэффициент сложности Бота
    int m_dist_mul = 1;

    std::vector <GameMove> solve(Board &board) override {
        // Обратные ходы
        constexpr std::pair<GameMove, GameMove> opp_moves[4] = {
                {GameMove::UP, GameMove::DOWN},
                {GameMove::DOWN, GameMove::UP},
                {GameMove::RIGHT, GameMove::LEFT},
                {GameMove::LEFT, GameMove::RIGHT}
        };
        // {Оценка, {Число ходов, Доска}}
        typedef  std::pair <std::pair <int, int>, uint64_t> state;
        // Хэш мапа с посещенными состояниями на ход, который в них приводит
        std::unordered_map <uint64_t , GameMove> closed_set;
        // Очередь с приоритетом
        std::priority_queue < state, std::vector<state>, std::greater<state> > open_set;

        // Добавление начальной вершины в мапу и очередь
        uint64_t packed = board.to_long_int(), final;
        open_set.push({{m_score_function(board), 0}, board.to_long_int()});
        closed_set.insert({packed, GameMove::NOPE});

        Board current_board;
        while(!open_set.empty()){
            // Получаем вершину с минимаьной(наилучшей) оценкой
            auto current = open_set.top();
            open_set.pop();
            current_board.load_from_long(current.second);

            // Решенная доска
            if(current_board.checkWin()){
                final = current_board.to_long_int();
                break;
            }

            // Пробуем из нее совершать ходы
            for(auto &&move: opp_moves){
                if(!current_board.isLegal(move.first)) {
                    continue;
                }

                current_board.applyMove(move.first);
                // Проверак
                if(closed_set.find(current_board.to_long_int()) == closed_set.end()){
                    open_set.push({
                            {
                                m_score_function(current_board) + current.first.second
                                                                / m_dist_mul ,
                                current.first.second+1
                            },
                            current_board.to_long_int()
                    });
                    closed_set.insert({current_board.to_long_int(), move.first});
                }
                current_board.applyMove(move.second);
            }

        }
        // Сюда записываем последовательность ходов приводящих к решению
        // Подразумеваются что они будут начинаться с конца
        std::vector <GameMove> moves;

        Board b;
        for(uint64_t cboard = final; cboard != packed; cboard = b.to_long_int()){
            auto move = closed_set[cboard];
            b.load_from_long(cboard);
            b.applyMove(opp_moves[((int)move) - 1].second);
            moves.push_back(move);
        }
        //std::reverse(moves.begin(), moves.end());
        return moves;
    }

public:
    explicit AStarSolver(int dist_mul):
            AbstractSolver<T>(), m_dist_mul(dist_mul){};

};


#endif //PROJECT_ASTARSOLVER_HH
