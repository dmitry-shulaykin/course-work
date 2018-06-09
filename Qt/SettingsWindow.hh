//
// Created by dima on 03.06.18.
//

#ifndef PROJECT_COMPUTERSETTINGSWINDOW_HH
#define PROJECT_COMPUTERSETTINGSWINDOW_HH

#include <QtWidgets>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QBoxLayout>
#include "GlobalSettings.hh"

class SettingsWindow : public QDialog {
	Q_OBJECT
	QLayout *m_layout, *difficulty_layout, *ai_layout;

	QGroupBox *m_ai_level;
	QGroupBox *m_difficulty;

public:
    SettingsWindow();
public slots:
    void handle_difficulty_clicked(){
            auto button_sender = qobject_cast<QRadioButton*>(sender());
            if(button_sender->text() == "Сложный")
                GlobalSettings::get().setDifficulty(GlobalSettings::Difficulty::HIGH);
            else if(button_sender->text() == "Легкий")
                GlobalSettings::get().setDifficulty(GlobalSettings::Difficulty::LOW);
            else if(button_sender->text() == "Средний")
                GlobalSettings::get().setDifficulty(GlobalSettings::Difficulty::MEDIUM);



    };

    void handle_ai_clicked(){
            auto button_sender = qobject_cast<QRadioButton*>(sender());
        if(button_sender->text() == "Сложный")
            GlobalSettings::get().setComputer(GlobalSettings::ComputerLevel::HIGH);
        else if(button_sender->text() == "Легкий")
            GlobalSettings::get().setComputer(GlobalSettings::ComputerLevel::LOW);
        else if(button_sender->text() == "Средний")
            GlobalSettings::get().setComputer(GlobalSettings::ComputerLevel::MEDIUM);
    };
};


#endif //PROJECT_COMPUTERSETTINGSWINDOW_HH
