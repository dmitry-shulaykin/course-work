//
// Created by dima on 18.03.18.
//

#ifndef PROJECT_COMPUTERWINDOW_H
#define PROJECT_COMPUTERWINDOW_H

#include "two-board-window.h"

class ComputerWindow : public TwoBoardWindow {
    void initPlayers(Game <4, 4>* game) override;
public:
    explicit ComputerWindow(QWidget *parent = nullptr);
    void init() override ;
};


#endif //PROJECT_COMPUTERWINDOW_H
