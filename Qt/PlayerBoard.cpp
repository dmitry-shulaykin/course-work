#include "PlayerBoard.h"


PlayerBoard::PlayerBoard(int player_id,
                         const Board &game,
                         bool enableInput,
                         bool enableHeader,
                         QWidget *parent) :
        QWidget(parent),
        player_id_(player_id),
        game(game),
        m_enable_header(enableHeader) {
    initWidgets();
    connect(this, SIGNAL(makeMove(GameMove)), this, SLOT(handleMove(GameMove)));
    if (enableInput)
        connectButtons();

    renderGame();
}

PlayerBoard::~PlayerBoard() {
    delete m_animator;
    delete frame;
    delete header;
    delete boxLayout;
}

void PlayerBoard::renderGame() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            Button *button = buttons[i][j];
            int x = buttons[i][j]->getX(), y = buttons[i][j]->getY();
            button->setText(QString::fromStdString(game.getStringData(x, y)));
            if (QString::fromStdString(game.getStringData(j, i)) == " ") {
                button->hide();
            } else {
                button->show();
            }
        }
    }

}

void PlayerBoard::initWidgets() {
    this->setFixedSize(width, height);

    // Creating Elements
    boxLayout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    header = new QBoxLayout(QBoxLayout::Direction::RightToLeft);
    turn_counter_label = new QLabel();
    header->addWidget(turn_counter_label);
    setActualInfo();
    QFont font = turn_counter_label->font();
    frame = new QFrame();
    frame->setGeometry(0, 0, 500, 500);
    frame->setFixedSize(500, 500);
    m_animator = new BoardAnimator();
    font.setPixelSize(48);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            buttons[i][j] = new Button(QString::number(i * w + j + 1),
                                       j, i, kButtonWidth, kButtonHeight, frame);
            buttons[i][j]->setFont(font);

            m_animator->addAnim(buttons[i][j]->getAnim());
        }
    }

    if (m_enable_header)
        boxLayout->addLayout(header);

    boxLayout->addWidget(frame);

    this->setLayout(boxLayout);
    this->setFixedSize(width, height + 30);
}


void PlayerBoard::handleClick() {

    if (!can_make_move_)
        return;

    Button *clicked_button = qobject_cast<Button *>(sender());

    int x = clicked_button->getX(), y = clicked_button->getY();

    if (clicked_button->text() != " ") {


        if (x > 0) {
            auto leftButton = buttons[y][x - 1];
            if (leftButton->text() == " ") {
                updateBoard(buttons[y][x], buttons[y][x - 1]);
                makeMove(GameMove::LEFT);
                return;
            }
        }

        if (x < w - 1) {
            auto rightButton = buttons[y][x + 1];
            if (rightButton->text() == " ") {
                updateBoard(buttons[y][x], buttons[y][x + 1]);

                makeMove(GameMove::RIGHT);
                return;
            }
        }

        if (y > 0) {
            auto upButton = buttons[y - 1][x];
            if (upButton->text() == " ") {
                updateBoard(buttons[y][x], buttons[y - 1][x]);
                makeMove(GameMove::UP);
                return;
            }
        }

        if (y < h - 1) {
            auto downButton = buttons[y + 1][x];
            if (downButton->text() == " ") {
                updateBoard(buttons[y][x], buttons[y + 1][x]);
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

    buttons[y1][x1]->moveTo(x2, y2);
    buttons[y2][x2]->moveTo(x1, y1);

    std::swap(buttons[y1][x1], buttons[y2][x2]);

    m_animator->startAnimation();
}

void PlayerBoard::handleMove(GameMove move) {
    game.applyMove(move);
    // renderGame();

    if (game.checkWin()) {
        confirmWin(player_id_);
    }

    can_make_move_ = false;
    setActualInfo();
}

void PlayerBoard::connectButtons() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            connect(buttons[i][j], SIGNAL(clicked()), this, SLOT(handleClick()));
        }
    }
}

void PlayerBoard::handleCanMove(GameMove m) {
    can_make_move_ = true;
    setActualInfo();
}

void PlayerBoard::setAbilityToMakeMove(bool can_move) {
    can_make_move_ = can_move;
}

void PlayerBoard::setActualInfo() {
    QString current_move_msg = "";

    if (can_make_move_) {
        current_move_msg = " (Текущий ход)";
    }

    turn_counter_label->setText("Игрок " + QString::number(player_id_)
                                + ", Ход №" + QString::number(game.getMoveCounter())
                                + current_move_msg);
}


