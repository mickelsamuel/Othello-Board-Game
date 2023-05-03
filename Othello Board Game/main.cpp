#include <iostream>
#include "Board.hpp"
#include "Player.hpp"
#include "Game.hpp"
int main(int argc, const char * argv[])
{
    Player p1("", Position::WHITE);
    Player p2("", Position::BLACK);
    Game(p1, p2);
}
