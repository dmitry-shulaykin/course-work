//
// Created by dima on 03.06.18.
//

#ifndef PROJECT_RULESWINDOW_HH
#define PROJECT_RULESWINDOW_HH


#include <QtWidgets>
#include "Logger.hh"

class RulesWindow : public QDialog{
Q_OBJECT
    QLayout *m_layout;
    QLabel *label;
public:
    RulesWindow() {
       m_layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
       label = new QLabel("Пятнашки – одна из известнейших миру головоломок.\n"
                          " Она представляет набор, в который входит квадратная коробка \n"
                          " сторона которой равна 4 сторонам костяшки, то есть. 4х4.\n"
                          " Внутри этой коробки 15 квадратных костяшек. \n"
                          "В коробке остается 1 свободное место под одну костяшку.\n"
                          " Цель игры – упорядочивание костяшек по порядку.\n"
                          " Концом игры считается, когда все костяшки от 1 до 15 стоят друг за другом.\n"
                          "\n"
                          "Игра поможет вам развить память и логическое мышление.\n"
                          " У вас будет развиваться возможность просчитывать ходы вперед без ошибок.\n"
                          " Сыграем?");

       m_layout->addWidget(label);
       setLayout(m_layout);
    }


};


#endif //PROJECT_RULESWINDOW_HH
