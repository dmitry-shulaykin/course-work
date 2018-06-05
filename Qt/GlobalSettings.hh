//
// Created by dima on 04.06.18.
//

#ifndef PROJECT_GLOBALSETTINGS_HH
#define PROJECT_GLOBALSETTINGS_HH

#include <iostream>

class GlobalSettings{

    int m_ai_max_level = 100;
    int m_shuffle_count = 40;
    float m_animation_speed = 1100.0;

    GlobalSettings() = default;
public:

    void setAiMaxLevel(int ai_max_level){
        m_ai_max_level = ai_max_level;
    }

    void setShuffleCount(int shuffle_count){
        m_shuffle_count = shuffle_count;
    }

    void setAnimationSpeed(float animation_speed){
        m_animation_speed = animation_speed;
    }

    int getAiMaxLevel() const {
        return m_ai_max_level;
    }

    int getShuffleCount() const {
        return m_shuffle_count;
    }

    float getAnimationSpeed() const {
        return m_animation_speed;
    }

    static GlobalSettings& get(){
        static GlobalSettings gs;
        return gs;
    }


};

#endif //PROJECT_GLOBALSETTINGS_HH
