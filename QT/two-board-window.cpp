#include <iostream>
#include "two-board-window.h"
#include <QMessageBox>

TwoBoardWindow::TwoBoardWindow(QWidget *parent) : QWidget(parent)
{

}

void TwoBoardWindow::initPlayers(Game <4, 4> *game) {
    first_player_ = new PlayerBoard(1, game);
    first_player_->setAbilityToMakeMove(1);
    second_player_ = new PlayerBoard(2, game);


    connect(first_player_, SIGNAL(makeMove(GameMove)), second_player_, SLOT(handleCanMove(GameMove)));
    connect(second_player_, SIGNAL(makeMove(GameMove)), first_player_, SLOT(handleCanMove(GameMove)));

    connect(first_player_, SIGNAL(confirmWin(int)), this, SLOT(handleWin(int)));
    connect(second_player_, SIGNAL(confirmWin(int)), this, SLOT(handleWin(int)));
}

void TwoBoardWindow::handleWin(int id) {
    first_player_->setAbilityToMakeMove(false);
    second_player_->setAbilityToMakeMove(false);

    QMessageBox msg_box;
    msg_box.setFixedSize(200, 60);
    QFont font = msg_box.font();
    font.setPixelSize(32);
    msg_box.setWindowTitle("Конец игры");
    msg_box.setFont(font);
    msg_box.setText("Игрок "+ QString::number(id) + " одержал победу!");
    msg_box.exec();
}

void TwoBoardWindow::init() {
    layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);

    auto game = new  Game<4, 4>();

    game->randomize((int)time(0), 256);

    this->initPlayers(game);

    layout->addWidget(first_player_);
    layout->addWidget(second_player_);

    setLayout(layout);
}
