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
        if(i == 1) btn->setChecked(true);
        if(i == 5) btn->setChecked(true);
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
}