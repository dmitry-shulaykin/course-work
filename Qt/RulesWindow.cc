//
// Created by dima on 04.06.18.
//
#include <QtWidgets/QBoxLayout>
#include "RulesWindow.hh"
#include "../Model/Board.hh"
#include "HelpBoard.hh"

RulesWindow::RulesWindow() {
    m_layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);

    setWindowTitle("Правила");

    move((QApplication::desktop()->screen()->rect().center()));

    m_label = new QLabel("Пятнашки – одна из известнейших миру головоломок.\n"
                         "Она представляет набор, в который входит квадратная коробка \n"
                         "сторона которой равна 4 сторонам костяшки, то есть. 4х4.\n"
                         "Внутри этой коробки 15 квадратных костяшек. \n"
                         "В коробке остается 1 свободное место под одну костяшку.\n"
                         "Цель игры – упорядочивание костяшек по порядку.\n"
                         "Концом игры считается, когда все костяшки от 1 до 15 стоят друг за другом.\n"
                         "Игра поможет вам развить память и логическое мышление.\n"
                         "У вас будет развиваться возможность просчитывать ходы вперед без ошибок.\n"
                         "Сыграем?");

    Board board;

    m_layout->addWidget(m_label);
    setLayout(m_layout);
}

RulesWindow::~RulesWindow() {
    delete m_layout;
    delete m_label;
}
