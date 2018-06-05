#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QWidget>
#include <thread>
#include <iostream>
#include "Animable.hh"
#include "GlobalSettings.hh"
#include "LinearAnimation.hh"


class Button : public QPushButton {
Q_OBJECT
protected:
    int x_, y_;
    LinearAnimation m_animation;

public:
    Button(const QString &text, int x, int y, int width, int height, QWidget *parent = nullptr);

    int getX() const { return x_; }

    int getY() const { return y_; }

    Animable *getAnim() { return &m_animation; }

    void moveTo(int x, int y);
};

#endif // BUTTON_H
