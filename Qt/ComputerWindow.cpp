//
// Created by dima on 18.03.18.
//

#include <iostream>
#include "ComputerWindow.h"
#include "ComputerBoard.h"

ComputerWindow::ComputerWindow(QWidget *parent): TwoBoardWindow(parent){
}

void ComputerWindow::initPlayers(Board * game) {
    first_player_ = new PlayerBoard(1, *game);
    first_player_->setAbilityToMakeMove(1);
    second_player_= new ComputerBoard(2, *game);

    connect(first_player_, SIGNAL(makeMove(GameMove)), second_player_, SLOT(handleCanMove(GameMove)));
    connect(second_player_, SIGNAL(makeMove(GameMove)), first_player_, SLOT(handleCanMove(GameMove)));

    connect(first_player_, SIGNAL(confirmWin(int)), this, SLOT(handleWin(int)));
    connect(second_player_, SIGNAL(confirmWin(int)), this, SLOT(handleWin(int)));
}
