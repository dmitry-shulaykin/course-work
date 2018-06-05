#ifndef TWOBOARDWINDOW_H
#define TWOBOARDWINDOW_H

#include "PlayerBoard.h"
#include <QWidget>

class TwoBoardWindow : public QWidget {
Q_OBJECT
protected:
    PlayerBoard *m_first_player = nullptr,
            *m_second_player = nullptr;

    QBoxLayout *m_layout = nullptr;

    virtual void initPlayers(const Board &game);

    virtual void connectSignals();

public:
    explicit TwoBoardWindow(QWidget *parent = nullptr);

    virtual void init();

    virtual ~TwoBoardWindow();

public slots:

    void handleWin(int id);

};


#endif // TWOBOARDWINDOW_H
