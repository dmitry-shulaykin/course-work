#include <iostream>
#include "TwoBoardWindow.h"
#include "WinnerWindow.hh"

TwoBoardWindow::TwoBoardWindow(QWidget *parent) : QWidget(parent) {
    m_layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
}

void TwoBoardWindow::initPlayers(const Board &game) {
    m_first_player = new PlayerBoard(1, game);
    m_first_player->setAbilityToMakeMove(1);
    m_second_player = new PlayerBoard(2, game);

    m_layout->addWidget(m_first_player);
    m_layout->addWidget(m_second_player);
}

void TwoBoardWindow::handleWin(int id) {
    m_first_player->setAbilityToMakeMove(false);
    m_second_player->setAbilityToMakeMove(false);

    WinnerWindow message(id);
}

TwoBoardWindow::~TwoBoardWindow() {
    delete m_first_player;
    delete m_second_player;

    delete m_layout;
}

void TwoBoardWindow::init() {
    Board game;
    game.randomize((int)time(0), GlobalSettings::get().getShuffleCount());
    initPlayers(game);
    connectSignals();
    setLayout(m_layout);
}

void TwoBoardWindow::connectSignals() {
    connect(m_first_player, SIGNAL(makeMove(GameMove)), m_second_player, SLOT(handleCanMove(GameMove)));
    connect(m_second_player, SIGNAL(makeMove(GameMove)), m_first_player, SLOT(handleCanMove(GameMove)));

    connect(m_first_player, SIGNAL(confirmWin(int)), this, SLOT(handleWin(int)));
    connect(m_second_player, SIGNAL(confirmWin(int)), this, SLOT(handleWin(int)));
}
