//
// Created by dima on 13.03.18.
//

#ifndef KURSOVAYA_VIEW_H
#define KURSOVAYA_VIEW_H

#include "../game.h"

template <size_t width, size_t  height>
class View {


public:
    static void display(Game <width, height>& p);
};

template<size_t width, size_t height>
void View<width, height>::display(Game<width, height>& p) {

    std::cout<<" turn " + std::to_string(p.getMoveCounter())<<std::endl;

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            cell c = p.getData(j,i);
            if(c <= 9){
                std::cout<<char(c +'0');
            }else if(c == '*'){
                std::cout<<'*';
            }else{
                std::cout<<char(c + 'a' - 10);
            }
        }
        std::cout<<std::endl;
    }

}

#endif //KURSOVAYA_VIEW_H
