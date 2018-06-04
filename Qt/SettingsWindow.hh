//
// Created by dima on 03.06.18.
//

#ifndef PROJECT_COMPUTERSETTINGSWINDOW_HH
#define PROJECT_COMPUTERSETTINGSWINDOW_HH


#include <QtWidgets>
#include "Logger.hh"
#include "GlobalSettings.hh"

class SettingsWindow : public QDialog {
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
        difficulty_layout->addWidget(m_difficulty_med);
        difficulty_layout->addWidget(m_difficulty_high);

        m_difficulty->setTitle("Сложность");
        m_difficulty->setLayout(difficulty_layout);
        m_ai_level->setTitle("Сложность компьютера");
        m_ai_level->setLayout(ai_layout);

        m_layout->addWidget(m_ai_level);
        m_layout->addWidget(m_difficulty);

        connect(m_difficulty_low, SIGNAL(clicked()), this, SLOT(handle_d1_clicked()));
        connect(m_difficulty_med, SIGNAL(clicked()), this, SLOT(handle_d2_clicked()));
        connect(m_difficulty_high, SIGNAL(clicked()), this, SLOT(handle_d3_clicked()));
        connect(m_ai_low, SIGNAL(clicked()), this, SLOT(handle_a1_clicked()));
        connect(m_ai_med, SIGNAL(clicked()), this, SLOT(handle_a2_clicked()));
        connect(m_ai_high, SIGNAL(clicked()), this, SLOT(handle_a3_clicked()));

        setWindowTitle("Настройки");
        setLayout(m_layout);
    }
public slots:
    void handle_d1_clicked(){
            GlobalSettings::get().setShuffleCount(32);
    };

    void handle_d2_clicked(){
            GlobalSettings::get().setShuffleCount(64);
    };

    void handle_d3_clicked(){
            GlobalSettings::get().setShuffleCount(128);
    };

    void handle_a1_clicked(){
            GlobalSettings::get().setAiMaxLevel(100);
    };

    void handle_a2_clicked(){
            GlobalSettings::get().setAiMaxLevel(90);
    };

    void handle_a3_clicked(){
            GlobalSettings::get().setAiMaxLevel(80);
    };




};


#endif //PROJECT_COMPUTERSETTINGSWINDOW_HH
