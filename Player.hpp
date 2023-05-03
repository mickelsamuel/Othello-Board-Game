#pragma once
#ifndef Player_hpp
#define Player_hpp
#include <string>
#include <stdio.h>
#endif /* Player_hpp */
class Player
{
public:
    void setname(std::string name);
    std::string getname();
    void setpiece(char piece);
    char getpiece();
    Player (std::string name, char piece);
    Player();
    
    bool operator==(const Player& other) const {
            return (name == other.name && piece == other.piece);
        }
    
private:
    std::string name;
    char piece;
};
