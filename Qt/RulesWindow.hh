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
	RulesWindow();


};


#endif //PROJECT_RULESWINDOW_HH
