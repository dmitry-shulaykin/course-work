#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QFrame>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QLabel>
#include "Button.h"
#include "QtWidgets"
#include "../Model/Board.hh"
#include "Animable.hh"
#include "BoardAnimator.hh"

class PlayerBoard : public QWidget {
Q_OBJECT

protected:
    int m_player_id;

    static constexpr int
            NUM_COLS = 4,
            NUM_ROWS = 4,
            BOARD_WIDTH = 500,
            BOARD_HEIGHT = 500,
            BUTTON_WIDTH = BOARD_WIDTH / NUM_COLS - 5,
            BUTTON_HEIGHT = BOARD_HEIGHT / NUM_ROWS - 5;

    bool m_can_move = false, m_enable_header;

    Board m_game;
    QFrame *m_frame;
    QBoxLayout *m_layout, *m_header;
    QLabel *m_turn_counter_label;
    BoardAnimator *m_animator;

    Button *m_buttons[NUM_ROWS][NUM_COLS];

    void initWidgets();

    void renderGame();

    void connectButtons();

    void setActualInfo();

    void updateBoard(Button *button1, Button *button2);

    void applyMove(GameMove move);

public:
    PlayerBoard(int player_id,
                const Board &game,
                bool enableInput = true, bool enableHeader = true,
                QWidget *parent = nullptr);

    ~PlayerBoard() override;

    void setAbilityToMakeMove(bool can_move);

signals:

    void makeMove(GameMove move);

    void confirmWin(int id);

private slots:

    void handleClick();

    void handleMove(GameMove move);

    virtual void handleCanMove(GameMove m);

};

#endif // MAINWINDOW_H
