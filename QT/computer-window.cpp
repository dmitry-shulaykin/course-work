//
// Created by dima on 18.03.18.
//

#include <iostream>
#include "computer-window.h"
#include "computer-board.h"

ComputerWindow::ComputerWindow(QWidget *parent): TwoBoardWindow(parent){

}

void ComputerWindow::initPlayers(Game<4, 4> *game) {
    std::cout<<"Computer Window"<<std::endl;
    first_player_ = new PlayerBoard(1, game);
    first_player_->setAbilityToMakeMove(1);
    second_player_= new ComputerBoard(2, game);

    connect(first_player_, SIGNAL(move(GameMove)), second_player_, SLOT(makeMove(GameMove)));
    connect(second_player_, SIGNAL(move(GameMove)), first_player_, SLOT(makeMove(GameMove)));
    connect(first_player_, SIGNAL(win(int)), this, SLOT(handleWin(int)));
    connect(second_player_, SIGNAL(win(int)), this, SLOT(handleWin(int)));
}

void ComputerWindow::init() {
    layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);

    auto game = new  Game<4, 4>();

    game->randomize(451, 100);

    this->initPlayers(game);

    layout->addWidget(first_player_);
    layout->addWidget(second_player_);

    setLayout(layout);
}

