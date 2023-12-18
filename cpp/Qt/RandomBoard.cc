//
// Created by dima on 04.06.18.
//

#include "RandomBoard.hh"

RandomBoard::RandomBoard(const Board &game): PlayerBoard(99, game, false, false),
    m_worker([this](){
        setAbilityToMakeMove(false);
        while(true) {
            GameMove move = m_game.getRandom();
            applyMove(move);
            m_game.applyMove(move);
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
})
{


}

RandomBoard::~RandomBoard() {
    m_worker.detach();
}
