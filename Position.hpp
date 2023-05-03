#pragma once
#ifndef Position_hpp
#define Position_hpp

#include <stdio.h>

#endif /* Position_hpp */
class Position
{
    public:
    bool canPlay();
    static const char EMPTY='.';
    static const char WHITE='W';
    static const char BLACK='B';
    static const char UNPLAYABLE='*';
    void setpiece(char piece);
    char getpiece();
    Position(int row, int col, char piece);
    Position();
    void setrow(int row);
    int getrow();
    void setcol(int col);
    int getcol();
    void flip();
    
    private:
    char piece;
    int row, col;
};
