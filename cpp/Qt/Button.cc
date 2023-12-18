//
// Created by dima on 04.06.18.
//

#include "Button.h"

Button::Button(const QString &text, int x, int y, int width, int height, QWidget *parent)
        : QPushButton(parent), x_(x), y_(y), m_animation(this) {
    this->setText(text);
    this->setFixedSize(width, height);
    this->setFixedSize(width, height);
    setGeometry(x * width, y * height, width, height);
    m_animation.init(x * width, y * height, x * width, y * height);
}

void Button::moveTo(int x, int y) {
    m_animation.init(x_ * width(), y_ * height(), x * width(), y * height());
    x_ = x;
    y_ = y;
}