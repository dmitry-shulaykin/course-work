//
// Created by dima on 29.05.18.
//

#ifndef PROJECT_ASTARSOLVER_HH
#define PROJECT_ASTARSOLVER_HH

#include <unordered_map>
#include "AbstractSolver.hh"

template <class K, class V>
class PriorityQueue
{
    std::vector<std::pair<K, V>> heap;

public:
    size_t size() const
    {
        return heap.size();
    }

    bool isEmpty() const
    {
        return heap.empty();
    }

    std::pair<K, V> peek() const
    {
        return heap[0];
    }

    void push(K key, V value)
    {
        heap.emplace_back(key, value);
        _siftUp();
    }

    std::pair<K, V> pop()
    {
        auto poppedValue = peek();
        size_t bottom = heap.size() - 1;

        if (bottom > 0)
        {
            _swap(0, bottom);
        }

        heap.pop_back();
        _siftDown();
        return poppedValue;
    }

private:
    bool _greater(uint32_t i, uint32_t j) const
    {
        return heap[i].first < heap[j].first;
    }

    void _swap(size_t i, size_t j)
    {
        std::swap(heap[i], heap[j]);
    }

    uint32_t _parent(uint32_t i) const
    {
        return ((i + 1) >> 1) - 1;
    }

    uint32_t _left(uint32_t i) const
    {
        return (i << 1) + 1;
    }

    uint32_t _right(uint32_t i) const
    {
        return (i + 1) << 1;
    }

    void _siftUp()
    {
        uint32_t node = heap.size() - 1;
        while (node > 0 && _greater(node, _parent(node)))
        {
            _swap(node, _parent(node));
            node = _parent(node);
        }
    }

    void _siftDown()
    {
        size_t node = 0;
        while (
            (_left(node) < heap.size() && _greater(_left(node), node)) ||
            (_right(node) < heap.size() && _greater(_right(node), node)))
        {
            size_t maxChild =
                _right(node) < heap.size() && _greater(_right(node), _left(node))
                    ? _right(node)
                    : _left(node);
            _swap(node, maxChild);
            node = maxChild;
        }
    }
};

template <class T>
class AStarSolverFork : public AbstractSolver<T>
{

    // Функция оценки
    using AbstractSolver<T>::m_score_function;

    // Коэффициент сложности Бота
    int m_dist_mul = 1;

    std::vector<GameMove> solve(Board &board) override
    {
        // Обратные ходы
        constexpr std::pair<GameMove, GameMove> opp_moves[4] = {
            {GameMove::UP, GameMove::DOWN},
            {GameMove::DOWN, GameMove::UP},
            {GameMove::RIGHT, GameMove::LEFT},
            {GameMove::LEFT, GameMove::RIGHT}};
        // Хэш мапа с посещенными состояниями на ход, который в них приводит
        std::unordered_map<uint64_t, GameMove> closed_set;
        // Очередь с приоритетом
        PriorityQueue<std::pair<int, int>, uint64_t> open_set;

        // Добавление начальной вершины в мапу и очередь
        uint64_t packed = board.to_long_int(), final;
        open_set.push({m_score_function(board), 0}, board.to_long_int());
        closed_set.insert({packed, GameMove::NOPE});

        Board current_board;

        // int best_score = m_score_function(board);

        while (!open_set.isEmpty())
        {
            // Получаем вершину с минимаьной(наилучшей) оценкой
            auto current = open_set.pop();

            auto boardInt = current.second;
            current_board.load_from_long(boardInt);

            // Решенная доска
            if (current_board.checkWin())
            {
                final = boardInt;
                break;
            }

            // auto calls = m_score_function.getCalls();
            // if (calls % 100 == 0) {
            //     std::cout << "calls = " << calls << ", best score = " << best_score << std::endl;
            // }


            // Пробуем из нее совершать ходы
            for (auto &&move : opp_moves)
            {
                if (!current_board.isLegal(move.first))
                {
                    continue;
                }

                current_board.applyMove(move.first);
                auto nextBoardInt = current_board.to_long_int();

                // Проверак
                if (closed_set.find(nextBoardInt) == closed_set.end())
                {
                    // best_score = std::min(m_score_function(current_board), best_score);

                    open_set.push(
                        std::make_pair(
                            (m_score_function(current_board) + current.first.second / m_dist_mul),
                            (current.first.second + 1)
                        ),
                        nextBoardInt
                    );
                    closed_set.insert({nextBoardInt, move.first});
                }
                current_board.applyMove(move.second);
            }
        }
        // Сюда записываем последовательность ходов приводящих к решению
        // Подразумеваются что они будут начинаться с конца
        std::vector<GameMove> moves;

        Board b;
        for (uint64_t cboard = final; cboard != packed; cboard = b.to_long_int())
        {
            auto move = closed_set[cboard];
            b.load_from_long(cboard);
            b.applyMove(opp_moves[((int)move) - 1].second);
            moves.push_back(move);
        }
        // std::reverse(moves.begin(), moves.end());
        return moves;
    }

public:
    explicit AStarSolverFork(int dist_mul) : AbstractSolver<T>(), m_dist_mul(dist_mul){};
};

#endif // PROJECT_ASTARSOLVER_HH
