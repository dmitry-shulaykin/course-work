//
// Created by dima on 18.03.18.
//

#include "MainPage.h"
#include "ComputerWindow.h"
#include "SingleBoardWindow.h"
#include "SettingsWindow.hh"
#include "RulesWindow.hh"

MainPage::MainPage(QWidget *parent) {

    this->setWindowTitle("Игра в 15");

    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    m_window = new TwoBoardWindow();
    m_window->init();
    m_menu_bar = new QMenuBar();

    std::array<std::pair<const char *, const char *>, 5> buttons{
            {
                    {"Играть одному", SLOT(startGameSingle())},
                    {"Играть вдвоем", SLOT(startGameWithHuman())},
                    {"Играть c компьютером", SLOT(startGameWithComputer())},
                    {"Правила", SLOT(openRulesDialog())},
                    {"Настройки", SLOT(openSettingsDialog())}
            }
    };

    for (auto &&button: buttons) {
        auto act = new QAction(button.first);
        connect(act, SIGNAL(triggered()), this, button.second);
        m_menu_bar->addAction(act);
    }

    setMenuBar(m_menu_bar);
    setCentralWidget(m_window);
}

void MainPage::startGameWithHuman() {
    delete m_window;
    m_window = new TwoBoardWindow();
    m_window->init();
    setCentralWidget(m_window);
}

void MainPage::startGameSingle() {
    delete m_window;
    m_window = new SingleBoardWindow();
    m_window->init();
    setCentralWidget(m_window);
}

void MainPage::startGameWithComputer() {
    delete m_window;
    m_window = new ComputerWindow();
    m_window->init();
    setCentralWidget(m_window);
}

void MainPage::openRulesDialog() {
    RulesWindow rules;
    rules.exec();
}

void MainPage::openSettingsDialog() {
    SettingsWindow settings;
    settings.exec();
}

MainPage::~MainPage() {
    delete m_window;

    for (auto &&act: m_menu_bar->children()) {
        delete act;
    }

    delete m_menu_bar;

}
