//
// Created by dima on 18.03.18.
//

#ifndef PROJECT_MAINPAGE_H
#define PROJECT_MAINPAGE_H

#include <QtWidgets>
#include "TwoBoardWindow.h"

class MainPage : public QMainWindow{
Q_OBJECT
public:
    explicit MainPage(QWidget *parent = nullptr);

private:
    TwoBoardWindow *window = nullptr;
    QToolButton *play_comp, *play_human, *play_single, *rules, *settings;
    QToolBar *toolbar;

private slots:
    void startGameSingle();
    void startGameWithHuman();
    void openSettingsDialog();
    void openRulesDialog();
    void startGameWithComputer();
};


#endif //PROJECT_MAINPAGE_H
