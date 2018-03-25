#ifndef BUTTON_H
#define BUTTON_H
#include <QToolButton>
#include <QWidget>

class Button : public QToolButton
{
Q_OBJECT
public:
    Button(const QString &text, int x, int y, int width, int height, QWidget *parent = 0);

    int getX() const {return x_;}
    int getY() const {return y_;}

private:
    int x_, y_;

};

#endif // BUTTON_H
