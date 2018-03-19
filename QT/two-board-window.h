#ifndef TWOBOARDWINDOW_H
#define TWOBOARDWINDOW_H

#include "player-board.h"
#include <QWidget>

class TwoBoardWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TwoBoardWindow(QWidget *parent = nullptr);
    virtual void init();
signals:

public slots:
    void handleWin(int id);

protected:
    PlayerBoard *first_player_ ,
                *second_player_;

    QBoxLayout* layout;

    virtual void initPlayers(Game <4, 4> *game);
};

#endif // TWOBOARDWINDOW_H
