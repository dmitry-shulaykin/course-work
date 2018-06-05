#include "SettingsWindow.hh"
//
// Created by dima on 04.06.18.
//

<<<<<<< HEAD
#include "SettingsWindow.hh"

SettingsWindow::SettingsWindow() {
    m_layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    ai_layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    difficulty_layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);

    move((QApplication::desktop()->screen()->rect().center()) );

    std::array < std::pair<const char*, const char*>, 6 > radio_settings = {
            {
                    {"Легкий",  SLOT(handle_difficulty_clicked())},
                    {"Средний", SLOT(handle_difficulty_clicked())},
                    {"Сложный", SLOT(handle_difficulty_clicked())},
                    {"Легкий",  SLOT(handle_ai_clicked())},
                    {"Средний", SLOT(handle_ai_clicked())},
                    {"Сложный", SLOT(handle_ai_clicked())},
            }
    };

    int i = 0;
    for(auto &&setting: radio_settings){
        auto btn = new QRadioButton(setting.first);

        if(i++ < 3){
            difficulty_layout->addWidget(btn);
            connect(btn, SIGNAL(clicked()), this, setting.second);
        }else{
            ai_layout->addWidget(btn);
            connect(btn, SIGNAL(clicked()), this, setting.second);
        }
    }
    m_ai_level = new QGroupBox();
    m_difficulty = new QGroupBox();

    m_difficulty->setTitle("Сложность");
    m_difficulty->setLayout(difficulty_layout);
    m_ai_level->setTitle("Сложность компьютера");
    m_ai_level->setLayout(ai_layout);

    m_layout->addWidget(m_ai_level);
    m_layout->addWidget(m_difficulty);

    setWindowTitle("Настройки");
    setLayout(m_layout);
=======
SettingsWindow::SettingsWindow(){
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
>>>>>>> 682bac403bef3fc465cdeb2b1b471ded2ddd025f
}