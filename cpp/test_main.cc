//
// Created by dima on 09.06.18.
//

#include "Model/Board.hh"
#include "Model/AStarSolver.hh"
#include "Model/ScoringFunctions.hh"
#include "Model/CachedSolver.hh"
#include "Model/BasicSolver.hh"
#include <bitset>

int main(){
    constexpr int num_test = 100;
    constexpr int shuffle = 1000;

    int sum_func_calls = 0;
    double sum_duration = 0;
    for(int i = 0; i < num_test; i++){
        Board b;
        b.randomize(i, shuffle);
        b.__debug();
        std::cout<<b.to_long_int()<<"   ";
        std::cout << std::bitset<64>(b.to_long_int()) << std::endl;
        auto s = std::chrono::system_clock::now();
        AStarSolver <SimpleScoreFunctor> solver(1);
        auto v = solver.solveWrap(b);
        while(v.size() > 0){
            b.applyMove(v.back());
            v.pop_back();
        }
        if(!b.checkWin()){
            std::cout<<"WRONG ANSWER";
            std::terminate();
        }
        std::cout << " total score calls: " << sum_func_calls<< std::endl;
        std::cout << " total duration: " << sum_duration << " ms" << std::endl;
        sum_duration += solver.getDurationMs();
        sum_func_calls += solver.getCallsCount();

    }

    std::cout << " avg func calls: " << sum_func_calls / num_test << std::endl;
    std::cout << " avg duration: " << sum_duration / num_test << " ms" << std::endl;

    return 0;
}