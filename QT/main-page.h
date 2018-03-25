//
// Created by dima on 18.03.18.
//

#ifndef PROJECT_MAINPAGE_H
#define PROJECT_MAINPAGE_H

#include <QtWidgets>
#include "two-board-window.h"

class MainPage : public QWidget{
Q_OBJECT
public:
    explicit MainPage(QWidget *parent = nullptr);

private:
    QBoxLayout *layout;
    TwoBoardWindow* window = nullptr;
    QToolButton *play_comp, *play_human;

private slots:
    void startGameWithHuman();
    void startGameWithComputer();
};


#endif //PROJECT_MAINPAGE_H
