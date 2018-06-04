//
// Created by dima on 03.06.18.
//

#include "Board.hh"

std::string Board::getStringData(int x, int y) const {
    return getData(x, y) ? std::to_string(getData(x, y)) : " ";
}

void Board::randomize(int seed, int num_moves) {
    std::mt19937 generator;
    generator.seed(seed);
    std::uniform_int_distribution<int> distribution(1, 4);
    GameMove move;
    while (num_moves--) {
        move = (GameMove) distribution(generator);
        while (!isLegal(move))
            move = (GameMove) distribution(generator);
        applyMove(move);
    }
    m_move_counter = 0;
}


int Board::getData(int x, int y) const {
    return m_data[y][x];
}

void Board::applyMove(GameMove move) {
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

Board::Board() {
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

Board::Board(const Board &other) : Board() {
    for (int i = 0; i < m_height; i++)
        for (int j = 0; j < m_width; j++)
            m_data[i][j] = other.m_data[i][j];
    m_free_x = other.m_free_x;
    m_free_y = other.m_free_y;
}

Board &Board::operator=(const Board &other) {
    for (int i = 0; i < m_height; i++)
        for (int j = 0; j < m_width; j++)
            m_data[i][j] = other.m_data[i][j];
    m_free_x = other.m_free_x;
    m_free_y = other.m_free_y;
}

Board::~Board() {
    for (int i = 0; i < m_width; i++)
        delete[] m_data[i];
    delete[] m_data;
}
