#include <iostream>
#include "SingleBoardWindow.h"
#include "WinnerWindow.hh"
#include "HelpBoard.hh"
#include <QMessageBox>

SingleBoardWindow::SingleBoardWindow(QWidget *parent) : TwoBoardWindow(parent){

}

void SingleBoardWindow::initPlayers(const Board &game) {
    m_first_player = new HelpBoard(1,  game);
    m_first_player->setAbilityToMakeMove(1);

    m_layout->addWidget(m_first_player);
}

void SingleBoardWindow::connectSignals() {
   // connect(m_first_player, SIGNAL(makeMove(GameMove)), m_first_player, SLOT(handleMove(GameMove)));
    connect(m_first_player, SIGNAL(makeMove(GameMove)), this, SLOT(refresh(GameMove)));
    connect(m_first_player, SIGNAL(confirmWin(int)), this, SLOT(handleWin(int)));
}

