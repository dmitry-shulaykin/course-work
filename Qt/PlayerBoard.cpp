#include "PlayerBoard.h"


PlayerBoard::PlayerBoard(int player_id,
                         const Board &game,
                         bool enableInput,
                         bool enableHeader,
                         QWidget *parent) :
        QWidget(parent),
        m_player_id(player_id),
        m_game(game),
        m_enable_header(enableHeader) {
    initWidgets();
    connect(this, SIGNAL(makeMove(GameMove)), this, SLOT(handleMove(GameMove)));
    if (enableInput)
        connectButtons();

    renderGame();
}

PlayerBoard::~PlayerBoard() {
    delete m_animator;
    delete m_frame;
    delete m_header;
    delete m_layout;
}

void PlayerBoard::renderGame() {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            Button *button = m_buttons[i][j];
            int x = m_buttons[i][j]->getX(), y = m_buttons[i][j]->getY();
            button->setText(QString::fromStdString(m_game.getStringData(x, y)));
            if (QString::fromStdString(m_game.getStringData(j, i)) == " ") {
                button->hide();
            } else {
                button->show();
            }
        }
    }

}

void PlayerBoard::initWidgets() {
    this->setFixedSize(BOARD_WIDTH, BOARD_HEIGHT);

    m_animator = new BoardAnimator();

    // Creating Elements
    m_turn_counter_label = new QLabel();
    setActualInfo();
    QFont font = m_turn_counter_label->font();

    m_header = new QBoxLayout(QBoxLayout::Direction::RightToLeft);
    m_header->addWidget(m_turn_counter_label);

    m_frame = new QFrame();

    m_frame->setGeometry(0, 0, BOARD_WIDTH, BOARD_HEIGHT);
    m_frame->setFixedSize(BOARD_WIDTH, BOARD_HEIGHT);

    font.setPixelSize(BUTTON_WIDTH/2);
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            m_buttons[i][j] = new Button(QString::number(i * NUM_COLS + j + 1),
                                       j, i, BUTTON_WIDTH, BUTTON_HEIGHT, m_frame);
            m_buttons[i][j]->setFont(font);

            m_animator->addAnim(m_buttons[i][j]->getAnim());
        }
    }

    m_layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    if (m_enable_header)
        m_layout->addLayout(m_header);

    m_layout->addWidget(m_frame);

    this->setLayout(m_layout);
    this->setFixedSize(BOARD_WIDTH, BOARD_HEIGHT + 30);
}


void PlayerBoard::handleClick() {

    if (!m_can_move)
        return;

    Button *clicked_button = qobject_cast<Button *>(sender());

    int x = clicked_button->getX(), y = clicked_button->getY();

    if (clicked_button->text() != " ") {


        if (x > 0) {
            auto leftButton = m_buttons[y][x - 1];
            if (leftButton->text() == " ") {
                updateBoard(m_buttons[y][x], m_buttons[y][x - 1]);
                makeMove(GameMove::LEFT);
                return;
            }
        }

        if (x < NUM_COLS - 1) {
            auto rightButton = m_buttons[y][x + 1];
            if (rightButton->text() == " ") {
                updateBoard(m_buttons[y][x], m_buttons[y][x + 1]);

                makeMove(GameMove::RIGHT);
                return;
            }
        }

        if (y > 0) {
            auto upButton = m_buttons[y - 1][x];
            if (upButton->text() == " ") {
                updateBoard(m_buttons[y][x], m_buttons[y - 1][x]);
                makeMove(GameMove::UP);
                return;
            }
        }

        if (y < NUM_ROWS - 1) {
            auto downButton = m_buttons[y + 1][x];
            if (downButton->text() == " ") {
                updateBoard(m_buttons[y][x], m_buttons[y + 1][x]);
                makeMove(GameMove::DOWN);
                return;
            }
        }
    }

}

void PlayerBoard::updateBoard(Button *button1, Button *button2) {
    m_animator->stopAnimation();

    int x1 = button1->getX();
    int y1 = button1->getY();

    int x2 = button2->getX();
    int y2 = button2->getY();

    m_buttons[y1][x1]->moveTo(x2, y2);
    m_buttons[y2][x2]->moveTo(x1, y1);

    std::swap(m_buttons[y1][x1], m_buttons[y2][x2]);

    m_animator->startAnimation();
}

void PlayerBoard::handleMove(GameMove move) {
    m_game.applyMove(move);
    // renderGame();

    if (m_game.checkWin()) {
        confirmWin(m_player_id);
    }

    m_can_move = false;
    setActualInfo();
}

void PlayerBoard::connectButtons() {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            connect(m_buttons[i][j], SIGNAL(clicked()), this, SLOT(handleClick()));
        }
    }
}

void PlayerBoard::handleCanMove(GameMove m) {
    m_can_move = true;
    setActualInfo();
}

void PlayerBoard::setAbilityToMakeMove(bool can_move) {
    m_can_move = can_move;
}

void PlayerBoard::setActualInfo() {
    QString current_move_msg = "";

    if (m_can_move) {
        current_move_msg = " (Текущий ход)";
    }

    m_turn_counter_label->setText("Игрок " + QString::number(m_player_id)
                                + ", Ход №" + QString::number(m_game.getMoveCounter())
                                + current_move_msg);
}

void PlayerBoard::applyMove(GameMove move) {
    std::array<std::pair<int, int>, 5> offs;
    offs[(int) GameMove::NOPE] = {0, 0};
    offs[(int) GameMove::UP] = {0, +1};
    offs[(int) GameMove::DOWN] = {0, -1};
    offs[(int) GameMove::LEFT] = {+1, 0};
    offs[(int) GameMove::RIGHT] = {-1, 0};

    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (m_buttons[i][j]->text() == " ") {
                updateBoard(m_buttons[i][j], m_buttons[i + offs[(int) move].second][j + offs[(int) move].first]);
                return;
            }
        }
    }

}


