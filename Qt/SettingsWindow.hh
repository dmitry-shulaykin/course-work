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

<<<<<<< HEAD

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
=======
	QRadioButton *m_ai_low,
		*m_ai_med,
		*m_ai_high;

	QRadioButton *m_difficulty_low,
		*m_difficulty_med,
		*m_difficulty_high;


public:
	SettingsWindow();
	public slots:
	void handle_d1_clicked() {
		GlobalSettings::get().setShuffleCount(32);
	};

	void handle_d2_clicked() {
		GlobalSettings::get().setShuffleCount(64);
	};

	void handle_d3_clicked() {
		GlobalSettings::get().setShuffleCount(128);
	};

	void handle_a1_clicked() {
		GlobalSettings::get().setAiMaxLevel(100);
	};

	void handle_a2_clicked() {
		GlobalSettings::get().setAiMaxLevel(90);
	};

	void handle_a3_clicked() {
		GlobalSettings::get().setAiMaxLevel(80);
	};
>>>>>>> 682bac403bef3fc465cdeb2b1b471ded2ddd025f

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
