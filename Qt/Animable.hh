//
// Created by dima on 03.06.18.
//

#ifndef PROJECT_ANIMABLE_HH
#define PROJECT_ANIMABLE_HH

class Animable {
public:
    Animable() = default;

    virtual bool nextStep(double delta_time) = 0;

    virtual void discardAnimation() = 0;
};


#endif //PROJECT_ANIMABLE_HH
