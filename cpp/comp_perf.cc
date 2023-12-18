//
// Created by dima on 09.06.18.
//

#include "Model/Board.hh"
#include "Model/AstarSolverFork.hh"
#include "Model/ScoringFunctions.hh"
#include "Model/CachedSolver.hh"
#include "Model/BasicSolver.hh"
#include <bitset>

void test(std::string str) {
    Board b;
    b.__debug();
    b.from_str(str);
    AStarSolverFork <SimpleScoreFunctor> solver(1);
    b.__debug();
    auto r = solver.solveWrap(b);
    std::cout << "duration: " << solver.getDurationMs() << " ms" << std::endl;
    std::cout << "func calls: " << solver.getCallsCount() << std::endl;
    std::cout << "steps: " << r.size() << std::endl;
}

int main(){
    test("ECA91B5736D408F2");
    test("59CE760134DF8B2A");

    return 0;
}