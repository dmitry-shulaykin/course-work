#include "player-board.h"
#include "../game.h"
#include <iostream>

PlayerBoard::PlayerBoard(int player_id,  Game<4, 4> * game, bool enableInput, QWidget *parent) :
    QWidget(parent), player_id_(player_id), game(new Game <4, 4> (*game))
{
    std::cout<<"inited new Player board"<<" enable input = "<<enableInput<<std::endl;
    initWidgets();
    connect(this, SIGNAL(move(GameMove)), this, SLOT(handleMove(GameMove)));
    if(enableInput)
        connectButtons();
    renderGame();
}

PlayerBoard::~PlayerBoard()
{
    delete header;
    delete boxLayout;
    delete game;
    for(int i = 0; i< h; i++){
        for(int j = 0; j< w; j++){
            delete buttons[i][j];
        }
    }
}

void PlayerBoard::renderGame(){
    for(int i = 0; i < h; i++){
        for(int j =0; j < w; j++){
            Button *button = buttons[i][j];
            button->setText(QString::fromStdString(game->getStringData(j, i)));
        }
    }

}

void PlayerBoard::initWidgets() {
    this->setFixedSize(width, height);
    constexpr int kButtonWidth = width / w;
    constexpr int kButtonHeight = height / h;

    // Creating Elements
    layout = new QGridLayout;
    layout->setSizeConstraint(QLayout::SetFixedSize);
    boxLayout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    header = new QLabel;
    setActualInfo();
    QFont font = header->font();

    font.setPixelSize(48);

    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            buttons[i][j] = new Button(QString::number(i*w+j+1),
                                       j, i, kButtonWidth, kButtonHeight);
            buttons[i][j]->setFont(font);
            layout->addWidget(buttons[i][j], i, j, 1, 1);
        }
    }

    boxLayout->addWidget(header);
    boxLayout->addItem(layout);

    this->setLayout(boxLayout);
}


void PlayerBoard::handleClick(){
    if(!can_make_move_)
        return;

    Button *clicked_button = qobject_cast<Button*>(sender());

    int x = clicked_button->getX(), y = clicked_button->getY();

    if(clicked_button->text() != ""){

        if(x > 0){
             auto leftButton = qobject_cast<Button*>(
                         layout->itemAtPosition(y, x-1)->widget());
             if(leftButton->text() == ""){
                 move(GameMove::LEFT);
                 return;
             }
        }

        if(x < w-1){
             auto rightButton = qobject_cast<Button*>(
                         layout->itemAtPosition(y, x+1)->widget());
             if(rightButton->text() == ""){
                 move(GameMove::RIGHT);
                 return;
             }
        }

        if(y > 0){
             auto upButton = qobject_cast<Button*>(
                         layout->itemAtPosition(y-1, x)->widget());
             if(upButton->text() == ""){
                 move(GameMove::UP);
                 return;
             }
        }

        if(y < h-1){
             auto downButton = qobject_cast<Button*>(
                         layout->itemAtPosition(y+1, x)->widget());
             if(downButton->text() == ""){
                 move(GameMove::DOWN);
                 return;
             }
        }

    }

}

void PlayerBoard::handleMove(GameMove move){
    game->applyMove(move);
    renderGame();
    if(game->checkWin()){
        win(player_id_);
    }

    can_make_move_ = false;
    setActualInfo();
}

void PlayerBoard::connectButtons() {
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            connect(buttons[i][j], SIGNAL(clicked()), this, SLOT(handleClick()));
        }
    }
}

void PlayerBoard::makeMove(GameMove m) {
    std::cout<<"Player Board make move evaluated"<<std::endl;
    can_make_move_ = true;
    setActualInfo();
    //GameMove next = getNextMove();
    //move(next);
}

void PlayerBoard::setAbilityToMakeMove(bool can_move) {
    can_make_move_ = can_move;
}

void PlayerBoard::setActualInfo() {
    QString current_move_msg = "";

    if(can_make_move_){
        current_move_msg = "(Текущий ход)";
    }

    header->setText("Игрок " + QString::number(player_id_)
                    + ", Ход №"+QString::number(game->getMoveCounter())
                    + current_move_msg);
}


