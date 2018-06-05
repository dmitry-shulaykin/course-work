//
// Created by dima on 03.06.18.
//

#include <termcap.h>
#include <array>
#include "Board.hh"

std::string Board::getStringData(int x, int y) const {
    return getData(x, y) ? std::to_string(getData(x, y)) : " ";
}

void Board::randomize(int seed, int num_moves) {
    while (num_moves--)
        applyMove(getRandom());
    m_move_counter = 0;
}


int Board::getData(int x, int y) const {
    return m_data[y][x];
}

GameMove Board::undoMove() {
    if(m_save_history){
        if(m_history.size()) {
            GameMove move = m_history.back();
            std::array<GameMove, 5> opp;
            opp[(int) GameMove::NOPE] = GameMove::NOPE;
            opp[(int) GameMove::UP] = GameMove::DOWN;
            opp[(int) GameMove::DOWN] = GameMove::UP;
            opp[(int) GameMove::LEFT] = GameMove::RIGHT;
            opp[(int) GameMove::RIGHT] = GameMove::LEFT;
            applyMove(opp[(int)move], false);
            m_move_counter--;
            m_history.pop_back();
            return opp[(int)move];
        }else{
            return GameMove::NOPE;
        }

    }else{
        return GameMove::NOPE;
    }
}

void Board::saveHistory(bool save_history) {
    m_save_history = save_history;
}

void Board::applyMove(GameMove move, bool save) {
    if (isLegal(move)) {
        switch (move) {
            case GameMove::UP:
                std::swap(m_data[m_free_y][m_free_x], m_data[m_free_y + 1][m_free_x]);
                m_free_y++;
                break;
            case GameMove::DOWN:
                std::swap(m_data[m_free_y][m_free_x], m_data[m_free_y - 1][m_free_x]);
                m_free_y--;
                break;
            case GameMove::LEFT:
                std::swap(m_data[m_free_y][m_free_x], m_data[m_free_y][m_free_x + 1]);
                m_free_x++;
                break;
            case GameMove::RIGHT:
                std::swap(m_data[m_free_y][m_free_x], m_data[m_free_y][m_free_x - 1]);
                m_free_x--;
                break;
        }
        if(save && m_save_history)
            m_history.push_back(move);
        m_move_counter++;
    } else {
        __debug();
        throw std::logic_error("Illegal Move");
    }

}


void Board::reset() {
    m_move_counter = 0;

    for (int i = 0; i < m_height; i++) {
        for (int j = 0; j < m_width; j++) {
            m_data[i][j] = (char) (i * m_width + j + 1);
        }
    }

    m_free_x = (int) m_width - 1;
    m_free_y = (int) m_height - 1;

    m_data[m_free_y][m_free_x] = 0;

}


int Board::getFreeX() const {
    return m_free_x;
}


int Board::getFreeY() const {
    return m_free_y;
}

Board::Board(bool save_history): m_save_history(save_history) {
    m_data = new int *[m_height];
    for (int i = 0; i < m_height; i++) m_data[i] = new int[m_width];
    reset();
}

bool Board::checkWin() const {
    for (int i = 0; i < m_height; i++)
        for (int j = 0; j < m_width; j++)
            if (i == m_height - 1 && j == m_width - 1)
                break;
            else if (m_data[i][j] != i * m_width + j + 1)
                return false;

    return true;
}

int Board::getMoveCounter() const {
    return m_move_counter;
}

bool Board::isLegal(GameMove move) const {
    switch (move) {
        case GameMove::UP:
            if (m_free_y == m_height - 1) return false;
            break;
        case GameMove::DOWN:
            if (m_free_y == 0) return false;
            break;
        case GameMove::LEFT:
            if (m_free_x == m_width - 1) return false;
            break;
        case GameMove::RIGHT:
            if (m_free_x == 0) return false;
            break;
        default:
            return true;
    }
    return true;
}

std::string Board::toString() {
    std::string str;
    for(int i = 0; i < m_height; i++){
        for(int j = 0; j < m_width; j++){
            str+=(char)((m_data[i][j] <= 9) ? m_data[i][j]+'0' : m_data[i][j]+'A' - 10);
        }
        str+='\n';
    }
    str+='\n';
    return str;
}

Board::Board(const Board &other) : Board() {
    for (int i = 0; i < m_height; i++)
        for (int j = 0; j < m_width; j++)
            m_data[i][j] = other.m_data[i][j];
    m_free_x = other.m_free_x;
    m_free_y = other.m_free_y;
}

uint64_t Board::to_long_int() const {
    uint64_t r = 0;
    for(int i = 0; i< m_height; i++){
        for(int j = 0; j < m_width;j++){
            unsigned int pos = (unsigned) i*m_width+j;
            uint64_t data = (unsigned)m_data[i][j];
            r|=data<<(pos*4u);
        }
    }
    return r;
}


void Board::load_from_long(uint64_t val){
    for(int i = 0; i< m_height; i++){
        for(int j = 0; j < m_width;j++){
            unsigned int pos = (unsigned) i*m_width+j;
            m_data[i][j] = (int)((val>>(pos*4u))&(15u));
            if(m_data[i][j] == 0){
                m_free_x = j;
                m_free_y = i;
            }
        }
    }
}

Board &Board::operator=(const Board &other) {
    for (int i = 0; i < m_height; i++)
        for (int j = 0; j < m_width; j++)
            m_data[i][j] = other.m_data[i][j];
    m_free_x = other.m_free_x;
    m_free_y = other.m_free_y;
	return *this;
}

Board::~Board() {
    for (int i = 0; i < m_width; i++)
        delete[] m_data[i];
    delete[] m_data;
}

GameMove Board::getRandom() {
    static std::mt19937 generator((int)time(0));
    static std::uniform_int_distribution<int> distribution(1, 4);
    GameMove move;
    move = (GameMove) distribution(generator);
    while (!isLegal(move))
        move = (GameMove) distribution(generator);
    return move;
}
