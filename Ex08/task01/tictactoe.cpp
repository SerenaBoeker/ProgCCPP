#include "tictactoe.hpp"
using namespace std;

class Player {
    protected:
        int turn;
        Player(int x);
    public:
        virtual void play(GameBoard *gameboard) const = 0;
        friend ostream& std::operator<<(ostream& os, Player& player);
};

class HumanPlayer : public Player {
    public:
        HumanPlayer(int x);
        virtual void play(GameBoard *gameboard) {

        };
};

class ComputerPlayer : public Player {
    private:
        Mode mode;
    public:
        ComputerPlayer(int x, Mode mode);
};

class GameBoard {
    private:
        int size;
        int** board;
    public:
        GameBoard(int size);

};

void printMenu() {
    cout << "Choose your game mode.\n" << "(1) Human vs. Human\n"
                                       << "(2) Human vs. Computer (Minimax)\n"
                                       << "(3) Human vs. Computer (Random)\n"
                                       << "(4) Computer (Minimax) vs. Computer (Minimax)\n"
                                       << "(5) Exit Program" << endl; 
}
