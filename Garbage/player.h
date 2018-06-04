//
// Created by dima on 13.03.18.
//

#ifndef KURSOVAYA_PLAYER_H
#define KURSOVAYA_PLAYER_H


#include <iostream>
#include "../game.h"

template <size_t width, size_t height>
class Player {

    int _score = 0;

    Game <width, height> _game;

public:
    Player() = default;
    explicit Player(Game <width, height> & game);

    GameMove makeMove();
    bool checkWin() const;
    void reset();

    void setScore(int score);
    void setGame(Game<width, height> & game);

    const Game<width, height>& getGame() const;
    int getScore() const;
};

template<size_t width, size_t height>
void Player<width, height>::setGame(const Game<width, height> &game) {
    _game = game;
}

template<size_t width, size_t height>
GameMove Player<width, height>::makeMove() {
    std::string str;
    std::cin>>str;

    GameMove move = GameMove::NOPE;

    if(str == "up")
        move = GameMove::UP;
    else if(str == "down")
        move = GameMove::DOWN;
    else if(str == "left")
        move = GameMove::LEFT;
    else if(str == "right")
        move = GameMove::RIGHT;

    _game.applyMove(move);

    return move;
}

template<size_t width, size_t height>
int Player<width, height>::getScore() const {
    return _score;
}

template<size_t width, size_t height>
void Player<width, height>::setScore(int score) {
    _score = score;
}

template<size_t width, size_t height>
void Player<width, height>::reset() {
    setScore(0);
    _game.reset();
}

template<size_t width, size_t height>
bool Player<width, height>::checkWin() const {
    return _game.checkWin();
}

template<size_t width, size_t height>
const Game<width, height> &Player<width, height>::getGame() const {
    return _game;
}

template<size_t width, size_t height>
Player<width, height>::Player(Game<width, height> &game):
    _game(game)
{

}

#endif //KURSOVAYA_PLAYER_H
