#include "button.h"

Button::Button(const QString &text, int x, int y, int width, int height, QWidget *parent)
    : QToolButton(parent), x_(x), y_(y)
{
    this->setText(text);
    this->setFixedSize(width, height);
    this->setFixedSize(width, height);
}
