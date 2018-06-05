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




};


#endif //PROJECT_COMPUTERSETTINGSWINDOW_HH
