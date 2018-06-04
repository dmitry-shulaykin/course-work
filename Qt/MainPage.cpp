//
// Created by dima on 18.03.18.
//

#include "MainPage.h"
#include "ComputerWindow.h"
#include "../Model/Board.hh"
#include "SingleBoardWindow.h"
#include "SettingsWindow.hh"
#include "RulesWindow.hh"

MainPage::MainPage(QWidget *parent) {

    this->setWindowTitle("Игра в 15");
    window = new TwoBoardWindow();
    window->init();

    play_comp = new QToolButton();
    play_human = new QToolButton();
    play_single = new QToolButton();
    rules = new QToolButton();
    settings = new QToolButton();

    play_single->setText("Играть одному");
    play_comp->setText("Играть с компьютером");
    play_human->setText("Играть с человеком");
    rules->setText("Правила");
    settings->setText("Настройки");

    toolbar = new QToolBar();
    toolbar->addWidget(play_single);
    toolbar->addWidget(play_comp);
    toolbar->addWidget(play_human);
    toolbar->addWidget(rules);
    toolbar->addWidget(settings);

    setCentralWidget(window);
    addToolBar(toolbar);

    //layout->addWidget(toolbar);
    //layout->addWidget(window);

    connect(play_single, SIGNAL(clicked()), this, SLOT(startGameSingle()));
    connect(play_comp, SIGNAL(clicked()), this, SLOT(startGameWithComputer()));
    connect(play_human, SIGNAL(clicked()), this, SLOT(startGameWithHuman()));
    connect(settings, SIGNAL(clicked()), this, SLOT(openSettingsDialog()));
    connect(rules, SIGNAL(clicked()), this, SLOT(openRulesDialog()));

    //setLayout(layout);
}

void MainPage::startGameWithHuman() {
    delete window;
    window = new TwoBoardWindow();
    window->init();
    setCentralWidget(window);
}

void MainPage::startGameSingle() {
    delete window;
    window = new SingleBoardWindow();
    window->init();
    setCentralWidget(window);
}

void MainPage::startGameWithComputer() {
    delete window;
    window = new ComputerWindow();
    window->init();
    setCentralWidget(window);
}

void MainPage::openRulesDialog() {
    RulesWindow *rules = new RulesWindow();
    rules->exec();
}

void MainPage::openSettingsDialog() {
    SettingsWindow *settings = new SettingsWindow();
    settings->exec();
}
