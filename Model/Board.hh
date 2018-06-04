#ifndef PROJECT_BOARD_HH
#define PROJECT_BOARD_HH

#include <random>
#include <string>
#include <stdexcept>
#include <iostream>

enum class GameMove{NOPE, UP = 1, DOWN = 2, RIGHT = 3, LEFT = 4};

class Board{
    int m_move_counter = 0,
        m_free_x, m_free_y,
        m_width = 4, m_height = 4;
    int **m_data;
public:
    Board();
    Board(const Board&);
    Board& operator=(const Board&);
    ~Board();


    void applyMove(GameMove move);
    void reset();

    int getFreeX() const;
    int getFreeY() const;

    int getWidth() const  { return m_width; }
    int getHeight() const { return m_height; }

    int getMoveCounter() const;

    bool checkWin() const;
    bool isLegal(GameMove move) const;

    void randomize(int seed, int num_moves);

    std::string getStringData(int x, int y) const;
    int getData(int x, int y) const;

    void __debug(){
        std::cout<<toString()<<std::endl;
    }

    uint64_t to_long_int() const{
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

    void load_from_long(uint64_t val){
        for(int i = 0; i< m_height; i++){
            for(int j = 0; j < m_width;j++){
                unsigned int pos = (unsigned) i*m_width+j;
                m_data[i][j] = (int)((val>>(pos*4u))&(15u));
                if(m_data[i][j] == 0){
                    m_free_x = j;
                    m_free_y = i;
                }
                //std::cout<<m_data[i][j]<<std::endl;
            }
        }
    }

    std::string toString(){
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

    static Board& getSolved(){
        static Board board;
        return board;
    }
};



#endif //PROJECT_BOARD_HH
