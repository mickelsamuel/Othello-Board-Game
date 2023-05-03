#include "Position.hpp"
Position::Position()
{
    
}
Position::Position(int row, int col, char piece)
{
    this->row=row;
    this->col=col;
    this->piece=piece;
}
void Position::setpiece(char piece)
{
    this->piece=piece;
}
char Position::getpiece()
{
    return piece;
}
void Position::setrow(int row)
{
    this->row=row;
}
int Position::getrow()
{
    return row;
}
void Position::setcol(int col)
{
    this->col=col;
}
int Position::getcol()
{
    return col;
}

void Position::flip() {
    if (piece == 'W') {
        piece = 'B';
    } else if (piece == 'B') {
        piece = 'W';
    }
}
