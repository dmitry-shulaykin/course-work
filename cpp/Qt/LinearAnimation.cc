//
// Created by dima on 04.06.18.
//
#include "LinearAnimation.hh"
#include "GlobalSettings.hh"


LinearAnimation::LinearAnimation(QWidget *target, double speed) :
        target(target), m_finished(true), m_speed(GlobalSettings::get().getAnimationSpeed()) {

}

void LinearAnimation::init(double s_x, double s_y, double f_x, double f_y) {
    m_x = m_start_x = s_x;
    m_y = m_start_y = s_y;
    m_end_x = f_x;
    m_end_y = f_y;
    m_finished = false;
    sx = 0;
    sy = 0;
}

bool LinearAnimation::nextStep(double delta_time) {
    if (m_finished) {
        return false;
    } else {
        double dx = m_end_x - m_start_x,
                dy = m_end_y - m_start_y;

        double d = abs(dx) + abs(dy);

        double vdx = (d != 0) ? m_speed * delta_time * dx / d : 0,
                vdy = (d != 0) ? m_speed * delta_time * dy / d : 0;

        m_x += vdx;
        m_y += vdy;
        sx += vdx;
        sy += vdy;

        if (abs(sx) > abs(dx) || abs(sy) > abs(dy)) {
            m_x = m_end_x;
            m_y = m_end_y;
            m_finished = true;
        }

        target->move((int) m_x, (int) m_y);
        return true;
    }
}

void LinearAnimation::discardAnimation() {
    m_x = m_end_x;
    m_y = m_end_y;
    m_finished = true;
    if (target)
        target->move((int) m_x, (int) m_y);
}
