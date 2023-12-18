#include <stdio.h>
#include <stdint.h>
#include <time.h>

enum GameMove
{
    NOPE,
    UP = 1,
    DOWN = 2,
    RIGHT = 3,
    LEFT = 4
};

struct Board
{
    unsigned char data[4][4];
    unsigned char free_x;
    unsigned char free_y;
};

void reset(struct Board *board)
{
    for (char i = 0; i < 4; i++)
    {
        for (char j = 0; j < 4; j++)
        {
            board->data[i][j] = i * 4 + j + 1;
        }
    }
}

char checkWin(struct Board *board)
{
    char num = 0;
    for (char i = 0; i < 4; i++)
    {
        for (char j = 0; j < 4; j++)
        {
            if (board->data[i][j] != num++)
            {
                return 0;
            }
            num++;
        }
    }

    return board->data[3][3] == 0;
}

char isLegalMove(struct Board *board, enum GameMove move)
{
    switch (move)
    {
    case UP:
        return board->free_y < 3;
    case DOWN:
        return board->free_y > 0;
    case LEFT:
        return board->free_x < 3;
    case RIGHT:
        return board->free_x > 0;
    default:
        return 0;
    }
}

void swapData(struct Board *board, int x1, int y1, int x2, int y2)
{
    unsigned char tmp = board->data[x1][y1];
    board->data[x1][y1] = board->data[x2][y2];
    board->data[x2][y2] = tmp;
}

void applyMove(struct Board *board, enum GameMove move)
{
    if (!isLegalMove(board, move))
    {
        return;
    }

    switch (move)
    {
    case UP:
        swapData(board, board->free_x, board->free_y, board->free_x, board->free_y + 1);
        board->free_y++;
        break;
    case DOWN:
        swapData(board, board->free_x, board->free_y, board->free_x, board->free_y - 1);
        board->free_y--;
        break;
    case LEFT:
        swapData(board, board->free_x, board->free_y, board->free_x + 1, board->free_y);
        board->free_x++;
        break;
    case RIGHT:
        swapData(board, board->free_x, board->free_y, board->free_x - 1, board->free_y);
        board->free_x--;
        break;
    default:
        break;
    }
}

void loadFromLong(struct Board *board, uint64_t data)
{
    for (char i = 0; i < 4; i++)
    {
        for (char j = 0; j < 4; j++)
        {
            unsigned char pos = i * 4 + j;
            board->data[i][j] = ((data >> (pos * 4u)) & (15u));
            if (board->data[i][j] == 0)
            {
                board->free_x = j;
                board->free_y = i;
            }
        }
    }
}

uint64_t toLong(struct Board *board)
{
    uint64_t r = 0;
    for (char i = 0; i < 4; i++)
    {
        for (char j = 0; j < 4; j++)
        {
            unsigned char pos = i * 4 + j;
            unsigned char data = board->data[i][j];
            r |= data << (pos * 4u);
        }
    }
    return r;
}

void from_str(struct Board *board, const char *str)
{
    int i = 0;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (str[i] >= 'A' && str[i] <= 'F') {
                board->data[y][x] = (char)(str[i] - 'A' + 10);
            }

            else if (str[i] >= '0' && str[i] <= '9') {
                board->data[y][x] = (char)(str[i] - '0');
            }

            if (board->data[y][x] == 0) {
                board->free_x = x;
                board->free_y = y;
            }

            i++;
        }
    }
}

void test(const char *str) {
    clock_t start = clock();
    struct Board b;

    from_str(&b, str);

    clock_t end = clock();
    double elapsed =  ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("Time measured: %.3f seconds. (%lld, %lld)\n", elapsed, start, end);

    // b.__debug();
    // b.from_str(str);
    // AStarSolverFork <SimpleScoreFunctor> solver(1);
    // b.__debug();
    // auto r = solver.solveWrap(b);
    // std::cout << "duration: " << solver.getDurationMs() << " ms" << std::endl;
    // std::cout << "func calls: " << solver.getCallsCount() << std::endl;
    // std::cout << "steps: " << r.size() << std::endl;
}

int main(void)
{
    test("ECA91B5736D408F2");
    return 0;
}