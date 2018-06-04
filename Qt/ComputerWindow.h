//
// Created by dima on 18.03.18.
//

#ifndef PROJECT_COMPUTERWINDOW_H
#define PROJECT_COMPUTERWINDOW_H

#include "TwoBoardWindow.h"
#include "../Model/Board.hh"

class ComputerWindow : public TwoBoardWindow {
    void initPlayers(Board *game) override;
public:
    explicit ComputerWindow(QWidget *parent = nullptr);
};


#endif //PROJECT_COMPUTERWINDOW_H
