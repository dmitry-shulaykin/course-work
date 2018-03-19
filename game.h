//
// Created by dima on 12.03.18.
//

#ifndef KURSOVAYA_GAME_H
#define KURSOVAYA_GAME_H

#include <cstddef>
#include <random>
#include <ostream>
#include <string>

typedef unsigned char cell;

enum class GameMove{NOPE, UP, DOWN, RIGHT, LEFT};


template <size_t width, size_t height>
class Game {
private:
    int _move_counter = 0;
    int _free_x, _free_y;
    cell _board[width][height];
public:
    Game();
    Game(const Game&) = default;
    Game& operator=(const Game&) = default;

    cell getData(int x, int y) const;

    void applyMove(GameMove move);
    void reset();

    int getFreeX() const;
    int getFreeY() const;

    int getMoveCounter() const;

    bool checkWin() const;
    bool isLegal(GameMove & move) const;

    void randomize(int seed, int num_moves);

    std::string getStringData(int x, int y) const;

};

template<size_t width, size_t height>
std::string Game<width, height>::getStringData(int x, int y) const {
        std::string ans = "";
        char c = getData(x, y);

        if(c < 10){
            return ans+=(c+'0');
        }else if(c != '*'){
            return ans+=(c+'a'-10);
        }

        return ans;
}

template<size_t width, size_t height>
void Game<width, height>::randomize(int seed, int num_moves) {
    std::mt19937 generator;
    generator.seed(seed);
    std::uniform_int_distribution<int> distribution(1,4);

    GameMove move;
    while(num_moves--) {
        move = (GameMove) distribution(generator);
        while(!isLegal(move)) move = (GameMove) distribution(generator);
        applyMove(move);
    }

    _move_counter = 0;
}

#define _DEBUG 1

template<size_t width, size_t height>
cell Game<width, height>::getData(int x, int y) const {
#ifdef _DEBUG
    if(x < 0 || x >= width || y < 0 || y > width)
        throw std::out_of_range("Move (" + std::to_string(x) + ", " + std::to_string(y) + ")" +
                                ", board size (" + std::to_string(width) + ", " + std::to_string(height) + ")");
#endif
    return _board[y][x];
}


template<size_t width, size_t height>
void Game<width, height>::applyMove(GameMove move) {
    if(isLegal(move)){
        switch(move){
            case GameMove::UP:
                std::swap(_board[_free_y][_free_x], _board[_free_y+1][_free_x]);
                _free_y++;
                break;
            case GameMove::DOWN:
                std::swap(_board[_free_y][_free_x], _board[_free_y-1][_free_x]);
                _free_y--;
                break;
            case GameMove::LEFT:
                std::swap(_board[_free_y][_free_x], _board[_free_y][_free_x+1]);
                _free_x++;
                break;
            case GameMove::RIGHT:
                std::swap(_board[_free_y][_free_x], _board[_free_y][_free_x-1]);
                _free_x--;
                break;
        }
        _move_counter++;
    }else{
        throw std::logic_error("Illegal Move");
    }

}

template<size_t width, size_t height>
void Game<width, height>::reset() {
    _move_counter = 0;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            _board[i][j] = (cell)(i*width + j+1);
        }
    }

    _free_x = (int) width-1;
    _free_y = (int) height-1;

    _board[_free_y][_free_x] = '*';

}


template<size_t width, size_t height>
int Game<width, height>::getFreeX() const {
    return _free_x;
}

template<size_t width, size_t height>
int Game<width, height>::getFreeY() const {
    return _free_y;
}

template<size_t width, size_t height>
Game<width, height>::Game() {
    reset();
}

template<size_t width, size_t height>
bool Game<width, height>::checkWin() const {

    //if(_free_x != width - 1 && _free_y != height - 1)
    //    return false;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(i == height-1 && j == width-1) continue;
            if(_board[i][j] != (cell)(i*width + j + 1))
                return false;
        }
    }

    return true;
}

template<size_t width, size_t height>
int Game<width, height>::getMoveCounter() const {
    return _move_counter;
}

template<size_t width, size_t height>
bool Game<width, height>::isLegal(GameMove &move) const {
    switch(move){
        case GameMove::UP:
            if(_free_y == height-1) return false; break;
        case GameMove::DOWN:
            if(_free_y == 0)  return false; break;
        case GameMove::LEFT:
            if(_free_x == width-1) return false; break;
        case GameMove::RIGHT:
            if(_free_x == 0) return false; break;
    }
    return true;
}

#endif //KURSOVAYA_GAME_H
