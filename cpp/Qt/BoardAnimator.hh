//
// Created by dima on 04.06.18.
//

#ifndef PROJECT_BOARDANIMATOR_HH
#define PROJECT_BOARDANIMATOR_HH

#include <thread>
#include <iostream>
#include <vector>
#include "Animable.hh"

class BoardAnimator {
    std::thread *animation_thread = nullptr;
    std::vector<Animable *> m_anim_objects;

    double desired_fps = 60;

    std::chrono::time_point<std::chrono::system_clock> last_check;

public:
    BoardAnimator() {
        m_anim_objects.clear();
    };

    ~BoardAnimator() {
        stopAnimation();
        m_anim_objects.clear();
    }

    void stopAnimation() {
        std::cout << "stopAnimation" << std::endl;

        if (animation_thread && animation_thread->joinable())
            animation_thread->detach();

        delete animation_thread;

        for (auto &&animable: m_anim_objects)
            animable->discardAnimation();

    }

    void startAnimation() {
        std::cout << "startAnimation" << std::endl;
        animation_thread = new std::thread([this]() {
            bool running = true;
            last_check = std::chrono::system_clock::now();

            while (running) {
                running = false;

                for (auto &&animable: m_anim_objects) {
                    auto now = std::chrono::system_clock::now();
                    double delta_time = (std::chrono::duration_cast<std::chrono::milliseconds>
                            (now - last_check).count()) / 1000.0;

                    running |= animable->nextStep(delta_time);
                }

                last_check = std::chrono::system_clock::now();

                std::this_thread::sleep_for(std::chrono::milliseconds((int) (1000.0 / desired_fps)));
            }
            std::cout << "AnimationEnded" << std::endl;
        });
    }

    void addAnim(Animable *anim) {
        m_anim_objects.push_back(anim);
    }
};


#endif //PROJECT_BOARDANIMATOR_HH
