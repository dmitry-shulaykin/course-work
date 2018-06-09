//
// Created by dima on 04.06.18.
//

#include "HelpBoard.hh"
#include "../Model/AStarSolver.hh"

HelpBoard::HelpBoard(int player_id, const Board &game, bool enableInput, bool enableHelp, QWidget *parent) :
        PlayerBoard(player_id, game) {
    setAbilityToMakeMove(true);
    m_game.saveHistory(true);

    std::array<std::pair<const char *, const char *>, 3> controls = {
            {
                    {"Назад", SLOT(handleUndo())},
                    {"Помочь", SLOT(handleHelp())},
                    {"Решить", SLOT(handleSolve())},
            }
    };

    for (auto &&control: controls) {
        auto btn = new QPushButton(control.first);
        m_header->addWidget(btn);
        connect(btn, SIGNAL(clicked()), this, control.second);
    }

}

void HelpBoard::handleUndo() {

    GameMove move = m_game.undoMove();
    if (move != GameMove::NOPE) {
        //makeMove(move);
        applyMove(move);
        setActualInfo();
    }
}

HelpBoard::~HelpBoard() {
    if (worker.joinable()) {
        worker.detach();
    }
}

void HelpBoard::handleSolve() {
    setAbilityToMakeMove(false);
    if (worker.joinable()) {
        setAbilityToMakeMove(false);
        worker.detach();
    }
    worker = std::thread([this]() {

        AStarSolver<SimpleScoreFunctor> solver(GlobalSettings::get().getComputerLevel());

        Board sample = m_game;

        moves = solver.solveWrap(sample);

        while (moves.size()) {
            applyMove(moves.back());
            m_game.applyMove(moves.back());
            makeMove(moves.back());
            moves.pop_back();
            setActualInfo();
        }

        setAbilityToMakeMove(true);

    });
}

void HelpBoard::handleHelp() {
    moves.clear();
    std::shared_ptr<AbstractScoreFunctor> score_func(new SimpleScoreFunctor());

    AStarSolver<SimpleScoreFunctor> solver(GlobalSettings::get().getComputerLevel());

    Board sample = m_game;

    moves = solver.solveWrap(sample);

    if (moves.size()) {
        applyMove(moves.back());
        m_game.applyMove(moves.back());
        setActualInfo();
    }

}

void HelpBoard::handleMove(GameMove move) {
    m_game.applyMove(move);
    if (m_game.checkWin()) {
        confirmWin(m_player_id);
    }

    setActualInfo();
}

