#ifndef SINGLEBOARDWINDOW_H
#define SINGLEBOARDWINDOW_H

#include "PlayerBoard.h"
#include "TwoBoardWindow.h"
#include <QWidget>

class SingleBoardWindow : public TwoBoardWindow
{
<<<<<<< HEAD
    Q_OBJECT
protected:
    void initPlayers(const Board &game) override;
    void connectSignals() override;
=======
	Q_OBJECT
>>>>>>> 682bac403bef3fc465cdeb2b1b471ded2ddd025f
public:
    explicit SingleBoardWindow(QWidget *parent = nullptr);

};

#endif // SINGLEBOARDWINDOW_H
