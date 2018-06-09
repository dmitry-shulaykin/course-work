//
// Created by dima on 29.05.18.
//

#ifndef PROJECT_ABSTRACTSOLVER_H
#define PROJECT_ABSTRACTSOLVER_H

#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <functional>
#include <thread>
#include <atomic>

#include "Board.hh"
#include "ScoringFunctions.hh"
template <class T>
class AbstractSolver {

protected:
    T m_score_function;

    double m_solve_duration;

    int m_score_function_calls;

    virtual std::vector<GameMove> solve(Board &board) = 0;

    AbstractSolver() : m_score_function() {
        this->m_score_function.init();
    }

public:

    std::vector<GameMove> solveWrap(Board &board) {

        std::vector<GameMove> ans;
        m_score_function.init();

        auto t = std::chrono::system_clock::now();
        Board sample = board;
        ans = this->solve(sample);
        auto d = std::chrono::system_clock::now() - t;

        m_score_function_calls = m_score_function.getCalls();
            m_solve_duration = (std::chrono::duration_cast
                    <std::chrono::milliseconds>(d).count());

        return ans;
    }

    double getDuration() const {
            return m_solve_duration;
    }

    int getCallsCount() const {
            return m_score_function_calls;
    }
};

#endif //PROJECT_ABSTRACTSOLVER_H
