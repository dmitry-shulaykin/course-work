//
// Created by dima on 18.03.18.
//

#include "MainPage.h"
#include "computer-window.h"

MainPage::MainPage(QWidget *parent) {
    layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    window = new TwoBoardWindow();
    window->init();

    play_comp = new QToolButton();
    play_human = new QToolButton();
    play_comp->setText("Play With Computer");
    play_human->setText("Play With Human");

    layout->addWidget(play_comp);
    layout->addWidget(play_human);
    layout->addWidget(window);

    connect(play_comp, SIGNAL(clicked()), this, SLOT(startGameWithComputer()));
    connect(play_human, SIGNAL(clicked()), this, SLOT(startGameWithHuman()));

    setLayout(layout);
}

void MainPage::startGameWithHuman() {
    delete window;
    window = new TwoBoardWindow();
    window->init();
    layout->addWidget(window);
}

void MainPage::startGameWithComputer() {
    delete window;
    window = new ComputerWindow();
    window->init();
    layout->addWidget(window);
}
