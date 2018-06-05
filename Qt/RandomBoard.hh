//
// Created by dima on 04.06.18.
//

#ifndef PROJECT_RANDOMBOARD_HH
#define PROJECT_RANDOMBOARD_HH


#include "PlayerBoard.h"

class RandomBoard : public PlayerBoard{
    std::thread m_worker;
    double speed;
public:
    RandomBoard(const Board &game);
    ~RandomBoard();
};


#endif //PROJECT_RANDOMBOARD_HH
