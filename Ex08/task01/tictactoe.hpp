#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>

enum class Mode {
    RANDOM, MINIMAX
};

class Player {
    protected:
        int turn;
        Player(int turn);
    public:
        virtual void play(GameBoard*) const = 0;
        friend std::ostream& operator<<(std::ostream& os, Player& player);
};

class HumanPlayer : public Player {
    public:
        HumanPlayer(int turn);
        virtual void play(GameBoard *gameboard);
};

class ComputerPlayer : public Player {
    private:
        Mode mode;
    public:
        ComputerPlayer(int turn, Mode mode);
};

class GameBoard {
    private:
        int size;
        int** board;
    public:
        GameBoard(int size);
        ~GameBoard();
        void insert(int, int, int);
        bool isFree(int, int);
        int getSize();
        int getWinnder();
        bool hasAvailableMoves();
        friend std::ostream& operator<<(std::ostream& os, GameBoard& gameboard);
};

class GameMaster {
    private:
        Player *player1;
        Player *player2;
        GameBoard gameboard;
    public:
        void start();
};

#endif