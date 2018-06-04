//
// Created by dima on 03.06.18.
//

#ifndef PROJECT_COMPUTERSETTINGSWINDOW_HH
#define PROJECT_COMPUTERSETTINGSWINDOW_HH


#include <QtWidgets>
#include "Logger.hh"

class SettingsWindow : public QDialog{
Q_OBJECT
    QLayout *m_layout, *difficulty_layout, *ai_layout;

    QGroupBox *m_ai_level;
    QGroupBox *m_difficulty;

    QRadioButton *m_ai_low,
                 *m_ai_med,
                 *m_ai_high;

    QRadioButton *m_difficulty_low,
                 *m_difficulty_med,
                 *m_difficulty_high;


public:
    SettingsWindow() {
        m_layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
        ai_layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
        difficulty_layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);

        m_ai_level = new QGroupBox();
        m_difficulty = new QGroupBox();

        m_ai_low = new QRadioButton("Легкий");
        m_ai_med = new QRadioButton("Средний");
        m_ai_high = new QRadioButton("Сложный");

        ai_layout->addWidget(m_ai_low);
        ai_layout->addWidget(m_ai_med);
        ai_layout->addWidget(m_ai_high);

        m_difficulty_low = new QRadioButton("Легкий");
        m_difficulty_med = new QRadioButton("Средний");
        m_difficulty_high = new QRadioButton("Сложный");

        difficulty_layout->addWidget(m_difficulty_low);
        difficulty_layout->addWidget(m_difficulty_high);
        difficulty_layout->addWidget(m_difficulty_med);

        m_difficulty->setTitle("Сложность");
        m_difficulty->setLayout(difficulty_layout);
        m_ai_level->setTitle("Сложность компьютера");
        m_ai_level->setLayout(ai_layout);

        m_layout->addWidget(m_ai_level);
        m_layout->addWidget(m_difficulty);

        setWindowTitle("Настройки");
        setLayout(m_layout);
    }


};


#endif //PROJECT_COMPUTERSETTINGSWINDOW_HH
