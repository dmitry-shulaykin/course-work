//
// Created by dima on 13.03.18.
//

#ifndef KURSOVAYA_SINGLEPLAYER_H
#define KURSOVAYA_SINGLEPLAYER_H


#include <memory>
#include <vector>

#include "../game.h"
#include "player.h"
#include "view.h"

#define DEFAULT_SEED 451
#define DEFAULT_MOVES 100

template <size_t width, size_t height>

class Multiplayer {

    static constexpr const char END_OF_GAME_MSG[] = "Game over",
                                WINNER_MSG[]      = "Winner: ",
                                WINNERS_MSG[]     = "Winners:\n";

    std::vector<std::shared_ptr<Player<width, height> > > _players;

    std::shared_ptr <View<width, height> > _view;

    bool _is_playing = false;

public:

    explicit Multiplayer(int num_players);

    void start();
    void endGame(std::vector <std::shared_ptr<Player<width,height> > > & winners);
};


template<size_t width, size_t height>
Multiplayer<width, height>::Multiplayer(int num_players) {
    for(int i = 0; i< num_players; i++){
        _players.emplace_back(new Player<width, height>());
    }
}

template<size_t width, size_t height>
void Multiplayer<width, height>::start() {

    Game<width, height> game;
    game.randomize(DEFAULT_SEED, DEFAULT_MOVES);

    for(auto &e: _players){
        e->reset();
        e->setGame(game);
    }

    _is_playing = true;

    while(_is_playing){
        int i = 0;
        for(auto &e: _players){
            _view->display(i++, *e);
            e->makeMove();
        }

        std::vector <std::shared_ptr<Player<width,height> > > winners;

        for(auto e: _players){
            if(e->checkWin())
                winners.push_back(e);
        }

        if(winners.size()){
            endGame(winners);
            _is_playing = false;
        }

    }



}

template<size_t width, size_t height>
void Multiplayer<width, height>::endGame(std::vector <std::shared_ptr<Player<width,height> > > & winners) {

    //std::cout<<END_OF_GAME_MSG<<std::endl;

    std::cout<<(winners.size() == 1) ? WINNER_MSG : WINNERS_MSG;

    int i = 0;
    for(auto e: winners){
        std::cout<<"Player " + std::to_string(i++)<<" score = "<<e->getScore()<<std::endl;
    }
}

#endif //KURSOVAYA_SINGLEPLAYER_H
