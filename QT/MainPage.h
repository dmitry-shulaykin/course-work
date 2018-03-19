//
// Created by dima on 18.03.18.
//

#ifndef PROJECT_MAINPAGE_H
#define PROJECT_MAINPAGE_H

#include <QtWidgets>
#include "two-board-window.h"

class MainPage : public QWidget{
    Q_OBJECT
    TwoBoardWindow* window = nullptr;
public:
    MainPage(QWidget *parent = nullptr);

    QBoxLayout *layout;
    QToolButton *play_comp, *play_human;

private:


private slots:
    void startGameWithHuman();
    void startGameWithComputer();

};


#endif //PROJECT_MAINPAGE_H
