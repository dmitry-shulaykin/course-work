//
// Created by dima on 18.03.18.
//

#include "main-page.h"
#include "computer-window.h"

MainPage::MainPage(QWidget *parent) {
    QBoxLayout *header = new QBoxLayout(QBoxLayout::Direction::LeftToRight);

    this->setWindowTitle("Игра в 15");
    layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    window = new TwoBoardWindow();
    window->init();

    play_comp = new QToolButton();
    play_human = new QToolButton();

    play_comp->setText("Играть с компьютером");
    play_human->setText("Играть с человеком");

    header->addWidget(play_comp);
    header->addWidget(play_human);

    layout->addItem(header);
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
