#pragma once
#ifndef Board_hpp
#define Board_hpp
#include "Position.hpp"
#include "Player.hpp"
#include <stdio.h>

#endif /* Board_hpp */

class Board
{
public:
    void drawBoard();
    static Board load();
    void play();
    static const int SIZE=8;
    Board();
    Board(Player p1, Player p2, int start);
    Board(std::string save_file);
    Position board[SIZE][SIZE];
    
    void getWinner();
    bool isFull();
    bool isValidMove(int row, int col, Position piece);
    void flipPieces();
private:
    void save();
    void takeTurn();
    Player p1;
    Player p2;
    Player cur;
    
    bool checkDirection(int row, int col, int drow, int dcol, Position piece);
};
