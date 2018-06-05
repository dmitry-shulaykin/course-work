//
// Created by dima on 03.06.18.
//

#ifndef PROJECT_RULESWINDOW_HH
#define PROJECT_RULESWINDOW_HH


#include <QtWidgets>
#include <QtWidgets/QLabel>
#include "RandomBoard.hh"

class RulesWindow : public QDialog {
Q_OBJECT
    QLayout *m_layout;
    QLabel *m_label;
public:
    RulesWindow();

    ~RulesWindow();
};


#endif //PROJECT_RULESWINDOW_HH
