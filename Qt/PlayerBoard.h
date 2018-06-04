#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Button.h"
#include "QtWidgets"
#include "../Model/Board.hh"
#include "Animable.hh"
#include "Logger.hh"
#include "BoardAnimator.hh"

class PlayerBoard : public QWidget {
Q_OBJECT

public:
    PlayerBoard(int player_id,
                const Board &game,
                bool enableInput = true, bool enableHeader = true,
                QWidget *parent = nullptr );

    ~PlayerBoard() override;

    void setAbilityToMakeMove(bool can_move);

protected:
    int player_id_;

    static constexpr int w = 4,
            h = 4,
            width = 500,
            height = 500,
            kButtonWidth = width / w - 5,
            kButtonHeight = height / h - 5;

    bool can_make_move_ = false, m_enable_header;
    Board game;
    QFrame *frame;
    QBoxLayout *boxLayout;
    QBoxLayout *header;
    QLabel *turn_counter_label;
    BoardAnimator *m_animator;

    Button *buttons[h][w];

    void initWidgets();

    void renderGame();

    void connectButtons();

    void setActualInfo();

    void updateBoard(Button *button1, Button *button2);

signals:
    void makeMove(GameMove move);

    void confirmWin(int id);

private slots:

    void handleClick();

    void handleMove(GameMove move);

    virtual void handleCanMove(GameMove m);

};

#endif // MAINWINDOW_H
