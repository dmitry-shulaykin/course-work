//
// Created by dima on 18.03.18.
//

#include <iostream>
#include "ComputerWindow.h"
#include "ComputerBoard.h"

ComputerWindow::ComputerWindow(QWidget *parent): TwoBoardWindow(parent){

}

void ComputerWindow::initPlayers(const Board &game) {
    m_first_player = new PlayerBoard(1, game);
    m_first_player->setAbilityToMakeMove(1);
    Board sample = game;
    m_second_player= new ComputerBoard(2, sample);

    m_layout->addWidget(m_first_player);
    m_layout->addWidget(m_second_player);
}
