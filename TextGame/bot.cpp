#include <cstring>
#include <climits>
#include <vector>
#include "iostream"
#include "stuff.h"



char move_names[][6] = {
        "nope",
        "up",
        "right",
        "down",
        "left"
};

int array_depth[81];




void getStar(char* array, int &x, int &y){
    for(int i = 0; i < SIZE; i++){
        if(array[i] == '*'){
            x = i%WIDTH;
            y = i/WIDTH;
            return;
        }
    }
}










int main(){
    srand(time(0));
    int hod = 0;
    std::cout<<"hod = "<<hod<<std::endl;
    char *array = getRandomArray();

    Move lastmove = NOPE;
    while(1){


        std::vector <Move> moves;
        solve_dfs(array, 0, lastmove, moves);
        if(!moves.size()){
            for(int i = 0; i < 10; i++)
                moves.push_back(static_cast<Move>(1 + rand()%4));
        }
        std::cout<<"num_moves="<<moves.size()<<std::endl;
        for(auto &e: moves){
            std::cout<<move_names[e]<<std::endl;
            applyMove(array, e);
        }

        lastmove = moves[0];

        debug(array, 0);


        if(checkWin(array)){
            printf("Congrats u re winner! Totol %d moves.\n", hod);
            break;
        }

        hod+=moves.size();

    }
    return 0;

}