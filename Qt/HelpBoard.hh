//
// Created by dima on 04.06.18.
//

#ifndef PROJECT_HELPBOARD_HH
#define PROJECT_HELPBOARD_HH

#include "ComputerBoard.h"

class HelpBoard : public PlayerBoard {
Q_OBJECT

    std::vector<GameMove> moves;
    std::thread worker;

public:
    HelpBoard(int player_id, const Board &game, bool enableInput = true, bool enableHelp = true, QWidget *parent = nullptr);
    ~HelpBoard();
public slots:

    void handleUndo();

    void handleSolve();

    void handleHelp();

    void handleMove(GameMove move);
signals:
};

#endif //PROJECT_HELPBOARD_HH
