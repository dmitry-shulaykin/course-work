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

class AbstractSolver {

protected:
    std::shared_ptr<AbstractScoreFunctor> m_score_function;


    virtual std::vector<GameMove> solve(Board &board) = 0;

    AbstractSolver(std::shared_ptr<AbstractScoreFunctor> score_function) :
            m_score_function(std::move(score_function)) {}

public:
    std::vector<GameMove> solveWrap(Board &board) {
        std::vector<GameMove> ans;

        m_score_function->init();

        auto t = std::chrono::system_clock::now();
        Board sample = board;
        ans = this->solve(sample);
        auto d = std::chrono::system_clock::now() - t;

        std::cout << "solved for " << (std::chrono::duration_cast<std::chrono::milliseconds>(d).count()) << "ms"
                  << std::endl;
        std::cout << "score_func_calls " << m_score_function->getCalls() << std::endl;
        return ans;
    }
};

#endif //PROJECT_ABSTRACTSOLVER_H
