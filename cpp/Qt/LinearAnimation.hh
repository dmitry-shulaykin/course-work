//
// Created by dima on 04.06.18.
//

#ifndef PROJECT_LINEARANIMATION_HH
#define PROJECT_LINEARANIMATION_HH


#include <QtWidgets/QWidget>
#include "Animable.hh"

class LinearAnimation : public Animable {
    double m_start_x, m_start_y;
    double m_end_x, m_end_y;
    double m_x, m_y;
    double m_speed;
    bool m_finished;
    double sx = 0, sy = 0;

    QWidget *target;

public:
    explicit LinearAnimation(QWidget *target, double speed = 600.0);

    void init(double s_x, double s_y, double f_x, double f_y);

    bool nextStep(double delta_time) override;

    void discardAnimation() override;
};

#endif //PROJECT_LINEARANIMATION_HH
