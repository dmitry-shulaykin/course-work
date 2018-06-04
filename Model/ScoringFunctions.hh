//
// Created by dima on 29.05.18.
//

#ifndef PROJECT_SCRORINGFUNCTIONS_HH
#define PROJECT_SCRORINGFUNCTIONS_HH

#include "Board.hh"

class AbstractScoreFunctor{
protected:
    int m_calls = 0;
public:
    virtual int operator()(const Board &board)  = 0;
    int getCalls() const { return  m_calls;};
    void init() { m_calls = 0;};
};

class SimpleScoreFunctor: public AbstractScoreFunctor {
public:
    int operator()(const Board &board) override {
        m_calls++;
        int score = 0;
        auto getStart = [&board](int c, int &x, int &y) {
            if (c != 0) {
                int cc = c - 1;
                y = cc / board.getWidth();
                x = cc % board.getHeight();
            } else {
                x = board.getWidth() - 1;
                y = board.getHeight() - 1;
            }
        };

        int w = board.getWidth(), h = board.getHeight();
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                int desire_x, desire_y;
                getStart(board.getData(j, i), desire_x, desire_y);

                int delta_x = abs(i - desire_y);
                int delta_y = abs(j - desire_x);

                score +=delta_x + delta_y;
            }
        }
        return score;
    }


};


#endif //PROJECT_SCRORINGFUNCTIONS_HH
