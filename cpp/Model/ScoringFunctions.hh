//
// Created by dima on 29.05.18.
//

#ifndef PROJECT_SCRORINGFUNCTIONS_HH
#define PROJECT_SCRORINGFUNCTIONS_HH

#include "Board.hh"

class AbstractScoreFunctor {
protected:
    int m_calls = 0;
public:
    virtual int operator()(const Board &board)  = 0;

    int getCalls() const { return m_calls; };

    void init() { m_calls = 0; };
};

class SimpleScoreFunctor : public AbstractScoreFunctor {

private:
    std::pair<int, int> getStart(char c) const {
        return (c != 0) ?
               (std::pair<int, int>){(c-1) / Board::HEIGHT, (c-1) % Board::WIDTH}:
               (std::pair<int, int>){Board::WIDTH - 1, Board::HEIGHT - 1};
    }
public:
    int operator()(const Board &board) override {
        m_calls++;
        int score = 0;
        for (int i = 0; i < Board::HEIGHT; i++) {
            for (int j = 0; j < Board::HEIGHT; j++) {
                auto desire = getStart(board.getData(j, i));
                int delta_x = abs(j - desire.second);
                int delta_y = abs(i - desire.first);
                score += delta_x + delta_y;
            }
        }
        return 2 * score;
    }
};


#endif //PROJECT_SCRORINGFUNCTIONS_HH
