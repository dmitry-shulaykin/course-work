#include <iostream>
#include "TwoBoardWindow.h"
#include "../Model/Board.hh"
#include "WinnerWindow.hh"
#include "GlobalSettings.hh"
#include <QMessageBox>

TwoBoardWindow::TwoBoardWindow(QWidget *parent) : QWidget(parent)
{
    //init();
}

void TwoBoardWindow::initPlayers(Board *game) {
    first_player_ = new PlayerBoard(1, *game);
    first_player_->setAbilityToMakeMove(1);
    second_player_ = new PlayerBoard(2, *game);

    layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
    layout->addWidget(first_player_);
    layout->addWidget(second_player_);

    setLayout(layout);

    connect(first_player_, SIGNAL(makeMove(GameMove)), second_player_, SLOT(handleCanMove(GameMove)));
    connect(second_player_, SIGNAL(makeMove(GameMove)), first_player_, SLOT(handleCanMove(GameMove)));

    connect(first_player_, SIGNAL(confirmWin(int)), this, SLOT(handleWin(int)));
    connect(second_player_, SIGNAL(confirmWin(int)), this, SLOT(handleWin(int)));
}

void TwoBoardWindow::handleWin(int id) {
    first_player_->setAbilityToMakeMove(false);
    second_player_->setAbilityToMakeMove(false);

    WinnerWindow message(id);
}

void TwoBoardWindow::init() {

    auto game = new Board();

    game->randomize((int)time(0), GlobalSettings::get().getShuffleCount());

    this->initPlayers(game);

    setLayout(layout);
}

