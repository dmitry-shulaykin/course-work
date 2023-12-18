//
// Created by dima on 04.06.18.
//

#ifndef PROJECT_GLOBALSETTINGS_HH
#define PROJECT_GLOBALSETTINGS_HH

#include <iostream>

class GlobalSettings{
public:
    enum class ComputerLevel {LOW, MEDIUM, HIGH};
    enum class Difficulty {LOW, MEDIUM, HIGH};
private:
    float m_animation_speed = 1100.0;
    ComputerLevel m_current_computer_level = ComputerLevel::HIGH;
    Difficulty m_current_difficulty  = Difficulty::MEDIUM;

    GlobalSettings() = default;
public:

    void setComputer(ComputerLevel level){
        m_current_computer_level = level;
    }

    void setDifficulty(Difficulty difficulty){
        m_current_difficulty = difficulty;
    }

    void setAnimationSpeed(float animation_speed){
        m_animation_speed = animation_speed;
    }

    int getComputerLevel() const {
        switch(m_current_computer_level){
            case ComputerLevel::HIGH: return 1;
            case ComputerLevel::LOW: return 3;
            case ComputerLevel::MEDIUM: return 2;
        }

        return 3;
    }

    int getShuffleCount() const {
        switch(m_current_difficulty){
            case Difficulty::HIGH: return 1024;
            case Difficulty::LOW: return 32;
            case Difficulty::MEDIUM: return 128;
        }

        return 32;
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
