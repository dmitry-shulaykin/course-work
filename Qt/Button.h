#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QWidget>
#include <thread>
#include <iostream>
#include "Animable.hh"
#include "GlobalSettings.hh"

class LinearAnimation : public Animable {
    double m_sx, m_sy;
    double m_fx, m_fy;

    double x, y;
    double speed;
    bool finished;
    double sx = 0, sy = 0;

    QWidget *target;

public:
    LinearAnimation(QWidget *target, double speed = 500.0) :
            target(target), finished(true), speed(GlobalSettings::get().getAnimationSpeed()) {
    }

    void init(double s_x, double s_y, double f_x, double f_y) {
        x = m_sx = s_x;
        y = m_sy = s_y;
        m_fx = f_x;
        m_fy = f_y;
        finished = false;
        sx = 0;
        sy = 0;
    }

    bool nextStep(double delta_time) override {
        if (finished) {
            return false;
        } else {
            double dx = m_fx - m_sx;
            double dy = m_fy - m_sy;

            double d = abs(dx) + abs(dy);

            double vdx = (d != 0) ? speed * delta_time * dx / d : 0;
            double vdy = (d != 0) ? speed * delta_time * dy / d : 0;

            x += vdx;
            y += vdy;

            sx += vdx;
            sy += vdy;

            if (abs(sx) > abs(dx) || abs(sy) > abs(dy)) {
                x = m_fx;
                y = m_fy;
                finished = true;
            }

            target->move((int) x, (int) y);
            return true;
        }
    }

    void discardAnimation() override {
        x = m_fx;
        y = m_fy;
        finished = true;
        if(target)
            target->move((int) x, (int) y);
    }

};

class Button : public QPushButton {
Q_OBJECT

public:
    Button(const QString &text, int x, int y, int width, int height, QWidget *parent = 0)
            : QPushButton(parent), x_(x), y_(y), m_animation(this) {
        this->setText(text);
        this->setFixedSize(width, height);
        this->setFixedSize(width, height);
        setGeometry(x * width, y * height, width, height);
        m_animation.init(x * width, y * height, x * width, y * height);
    }


    int getX() const { return x_; }

    int getY() const { return y_; }

    Animable *getAnim() { return &m_animation; }

    void moveTo(int x, int y) {
        m_animation.init(x_ * width(), y_ * height(), x * width(), y * height());
        x_ = x;
        y_ = y;
    }


private:

    int x_, y_;
    LinearAnimation m_animation;
};

#endif // BUTTON_H
