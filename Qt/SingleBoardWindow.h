#ifndef SINGLEBOARDWINDOW_H
#define SINGLEBOARDWINDOW_H

#include "PlayerBoard.h"
#include "TwoBoardWindow.h"
#include <QWidget>

class SingleBoardWindow : public TwoBoardWindow
{
	Q_OBJECT
public:
    explicit SingleBoardWindow(QWidget *parent = nullptr);
signals:

public slots:
    void handleWin(int id);

protected:
    PlayerBoard *player_;
    QBoxLayout *layout;

    void initPlayers(Board *game) override;
};

#endif // SINGLEBOARDWINDOW_H
