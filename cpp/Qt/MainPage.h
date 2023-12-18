//
// Created by dima on 18.03.18.
//

#ifndef PROJECT_MAINPAGE_H
#define PROJECT_MAINPAGE_H

#include <QtWidgets>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMainWindow>
#include "TwoBoardWindow.h"

class MainPage : public QMainWindow {
Q_OBJECT
public:
    explicit MainPage(QWidget *parent = nullptr);

    ~MainPage();

private:
    TwoBoardWindow *m_window = nullptr;
    QMenuBar *m_menu_bar = nullptr;
private slots:

    void startGameSingle();

    void startGameWithHuman();

    void openSettingsDialog();

    void openRulesDialog();

    void startGameWithComputer();
};


#endif //PROJECT_MAINPAGE_H
