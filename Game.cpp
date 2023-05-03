#include <iostream>
#include "Game.hpp"
#include <string>
#include "Player.hpp"
#include <iostream>
Game::Game()
{}
Game::Game(Player p1, Player p2)
{
    this->p1=p1;
    this->p2=p2;
    int choice = 0;
    while (choice != 1 && choice != 2 && choice != 3) {
        std::cout << "1. Start a New Game" << std::endl << std::endl << "2. Load a Game" << std::endl << std::endl << "3. Quit" << std::endl << std::endl;
        std::cin >> choice;
        if (choice == 1) {
            start();
        } else if (choice == 2) {
            board=Board::load();
            board.play();
        } else if (choice == 3) {
            exit(0);
        } else {
            std::cout << "Invalid choice. Please enter 1, 2, or 3." << std::endl;
        }
    }
}

void Game::start()
{
    std::string name1, name2;
    std::cout<<std::endl <<"Enter first player's name: ";
    std::cin >> name1;
    std::cout<< std::endl << "Enter second player's name: ";
    std::cin >> name2;
    std::cout << "Enter 1 or 2 for each starting postion: ";
    std::cin >> starts;
    
    
    p1.setname(name1);
    p2.setname(name2);
    
    board=Board(p1, p2, starts);
    board.play();
    
}
