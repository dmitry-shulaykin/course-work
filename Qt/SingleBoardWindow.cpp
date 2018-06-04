#include <iostream>
#include "SingleBoardWindow.h"
#include "WinnerWindow.hh"
#include <QMessageBox>

SingleBoardWindow::SingleBoardWindow(QWidget *parent) : TwoBoardWindow(parent){

}

void SingleBoardWindow::initPlayers(Board *game) {
    layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);

    player_ = new PlayerBoard(1, *game);
    player_->setAbilityToMakeMove(1);

    layout->addWidget(player_);
    setLayout(layout);

    connect(player_, SIGNAL(makeMove(GameMove)), player_, SLOT(handleCanMove(GameMove)));
    connect(player_, SIGNAL(confirmWin(int)), this, SLOT(handleWin(int)));
}

void SingleBoardWindow::handleWin(int id) {
    player_->setAbilityToMakeMove(false);
    WinnerWindow message(id);
}

