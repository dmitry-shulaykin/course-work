#ifndef SINGLEBOARDWINDOW_H
#define SINGLEBOARDWINDOW_H

#include "PlayerBoard.h"
#include "TwoBoardWindow.h"
#include <QWidget>

class SingleBoardWindow : public TwoBoardWindow
{
    Q_OBJECT
protected:
    void initPlayers(const Board &game) override;
    void connectSignals() override;
public:
    explicit SingleBoardWindow(QWidget *parent = nullptr);

};

#endif // SINGLEBOARDWINDOW_H
