#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "button.h"
#include "QtWidgets"
#include "../game.h"

class PlayerBoard : public QWidget{
    Q_OBJECT

public:
    PlayerBoard(int player_id,
                Game<4, 4> * game,
                bool enableInput = true,
                QWidget *parent = nullptr);

     ~PlayerBoard() override;

    void setAbilityToMakeMove(bool can_move);

protected:
    int player_id_;

    static constexpr int w = 4,
                         h = 4,
                         width = 500,
                         height = 500,
                         kButtonWidth = width / w,
                         kButtonHeight = height / h;

    bool can_make_move_ = false;
    Game<4, 4>  *game;

    QGridLayout *layout;
    QBoxLayout  *boxLayout;
    QLabel      *header;

    Button *buttons[h][w];

    void initWidgets();
    void renderGame();
    void connectButtons();
    void setActualInfo();

signals:
    void makeMove(GameMove move);
    void confirmWin(int id);

private slots:
    void handleClick();
    void handleMove(GameMove move);
    virtual void handleCanMove(GameMove m);

};

#endif // MAINWINDOW_H
