#ifndef PROJECT_BOARD_HH
#define PROJECT_BOARD_HH

#include <random>
#include <string>
#include <stdexcept>
#include <iostream>

enum class GameMove {
    NOPE, UP = 1, DOWN = 2, RIGHT = 3, LEFT = 4
};

class Board {


    int m_move_counter = 0,
        m_free_x, m_free_y,
        m_width = 4, m_height = 4;

    char m_data[4][4];
    bool m_save_history = false;
    std::vector<GameMove> m_history;
public:
    static constexpr int WIDTH = 4, HEIGHT = 4;

    Board(bool save_history = false);

    Board(const Board &);

    Board &operator=(const Board &);

    ~Board();


    void applyMove(GameMove move, bool save = true);

    GameMove undoMove();

    void reset();

    int getFreeX() const;

    int getFreeY() const;

    int getWidth() const { return m_width; }

    int getHeight() const { return m_height; }

    int getMoveCounter() const;

    bool checkWin() const;

    bool isLegal(GameMove move) const;

    void randomize(int seed, int num_moves);

    std::string getStringData(int x, int y) const;

    int getData(int x, int y) const;

    void __debug() {
        std::cout << toString() << std::endl;
    }

    uint64_t to_long_int() const;

    void load_from_long(uint64_t val);

    void from_str(std::string str);

    void saveHistory(bool save_history);

    std::string toString();

    static Board &getSolved() {
        static Board board;
        return board;
    }

    GameMove getRandom(int seed = -1);
};


#endif //PROJECT_BOARD_HH
