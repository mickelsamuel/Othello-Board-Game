#pragma once
#ifndef Game_hpp
#define Game_hpp
#include "Board.hpp"
#include "Player.hpp"
#include <stdio.h>

#endif /* Game_hpp */
class Game
{
public:
    Game();
    Game(Player p1, Player p2);
    void start();
    
private:
    
    Player p1;
    Player p2;
    int starts;
    Board board;
    
};
