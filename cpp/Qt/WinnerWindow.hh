//
// Created by dima on 03.06.18.
//

#ifndef PROJECT_WINNERWINDOW_HH
#define PROJECT_WINNERWINDOW_HH

#include <QtWidgets/QMessageBox>


class WinnerWindow : public QMessageBox {
public:
    WinnerWindow(int id) {
        move((QApplication::desktop()->screen()->rect().center()));

        setFixedSize(200, 60);
        QFont font = this->font();
        font.setPixelSize(32);
        setWindowTitle("Конец игры");
        setFont(font);
        setText("Игрок " + QString::number(id) + " одержал победу!");
        exec();
    }
};


#endif //PROJECT_WINNERWINDOW_HH
