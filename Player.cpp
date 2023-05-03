#include "Board.hpp"
#include "Position.hpp"
#include <iostream>
using namespace std;
#include "Player.hpp"
Player::Player()
{
    
}
Player::Player(std::string name, char piece)
{
    this->name=name;
    this->piece=piece;
}
void Player::setname(std::string name)
{
    this->name=name;
}
std::string Player::getname()
{
    return name;
}
void Player::setpiece(char piece)
{
    this->piece=piece;
}
char Player::getpiece()
{
    return piece;
}
