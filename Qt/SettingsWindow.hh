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

            int d = 32;
            if(button_sender->text() == "Сложный")
                    d = 256;
            else if(button_sender->text() == "Средний")
                    d = 128;


            GlobalSettings::get().setShuffleCount(d);
    };

    void handle_ai_clicked(){
            auto button_sender = qobject_cast<QRadioButton*>(sender());

            int d = 130;
            if(button_sender->text() == "Сложный")
                    d = 110;
            else if(button_sender->text() == "Средний")
                    d = 120;

            GlobalSettings::get().setAiMaxLevel(d);
    };
};


#endif //PROJECT_COMPUTERSETTINGSWINDOW_HH
