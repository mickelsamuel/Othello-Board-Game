#include <fstream>
#include <stdlib.h>
#include <iostream>
using namespace std;
#include "Board.hpp"
#include "Position.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include <sstream>
// Constructor for an empty board
Board::Board() {
    // Initialize all positions to empty
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            board[row][col] = Position(row, col, Position::EMPTY);
        }
    }
}

// Constructor for a new game with two players and a starting position option
Board::Board(Player p1, Player p2, int start) {
    // Initialize all positions to empty
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            board[row][col] = Position(row, col, Position::EMPTY);
        }
    }

    // Set the starting positions based on the option
    if (start == 1) {
        board[2][2].setpiece(Position::WHITE);
        board[2][3].setpiece(Position::WHITE);
        board[2][4].setpiece(Position::BLACK);
        board[2][5].setpiece(Position::BLACK);
        board[3][2].setpiece(Position::WHITE);
        board[3][3].setpiece(Position::WHITE);
        board[3][4].setpiece(Position::BLACK);
        board[3][5].setpiece(Position::BLACK);
        board[4][2].setpiece(Position::BLACK);
        board[4][3].setpiece(Position::BLACK);
        board[4][4].setpiece(Position::WHITE);
        board[4][5].setpiece(Position::WHITE);
        board[5][2].setpiece(Position::BLACK);
        board[5][3].setpiece(Position::BLACK);
        board[5][4].setpiece(Position::WHITE);
        board[5][5].setpiece(Position::WHITE);
        board[2][0].setpiece(Position::UNPLAYABLE);
        board[3][0].setpiece(Position::UNPLAYABLE);
        board[4][0].setpiece(Position::UNPLAYABLE);
        board[5][0].setpiece(Position::UNPLAYABLE);

    }
    else if (start==2){
        board[3][3].setpiece(Position::WHITE);
        board[3][4].setpiece(Position::BLACK);
        board[4][3].setpiece(Position::BLACK);
        board[4][4].setpiece(Position::WHITE);
        board[2][0].setpiece(Position::UNPLAYABLE);
        board[3][0].setpiece(Position::UNPLAYABLE);
        board[4][0].setpiece(Position::UNPLAYABLE);
        board[5][0].setpiece(Position::UNPLAYABLE);
    }
    
    this->p1 = p1;
    this->p2 = p2;
    this->cur = p1;
}

// Draw the current state of the board to the console
void Board::drawBoard() {
    // Print the column numbers
    system("clear");
    cout << "  ";
    for (int col = 0; col < SIZE; col++) {
        cout << col << " ";
    }
    cout << endl;

    // Print the row number and contents for each row
    for (int row = 0; row < SIZE; row++) {
        cout << row << " ";
        for (int col = 0; col < SIZE; col++) {
            cout << board[row][col].getpiece() << " ";
        }
        cout << endl;
    }
}

//switch turns
void Board::takeTurn() {
    if (cur == p1) {
        cur = p2;
    }
    else {
        cur = p1;
    }
}

bool Board::isFull()  {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col].getpiece() == Position::EMPTY) {
                return false;
            }
        }
    }
    return true;
}

 void Board::getWinner()
{
    int whiteCount = 0;
    int blackCount = 0;
    
    // Count the number of white and black pieces on the board
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            if (board[row][col].getpiece() == Position::WHITE)
            {
                whiteCount++;
            }
            else if (board[row][col].getpiece() == Position::BLACK)
            {
                blackCount++;
            }
        }
    }
    
    // Determine the winner based on the piece count
    if (whiteCount > blackCount)
    {
        std::cout << "White is the winner";
    }
    else if (blackCount > whiteCount)
    {
        std::cout << "Black is the winner";
    }
    else if (blackCount==whiteCount)
    {
        std::cout << "Tie";
    }
}

bool Board::checkDirection(int row, int col, int drow, int dcol, Position piece) {
    // Check if the first piece in this direction is an opponent's piece
    int r = row + drow;
    int c = col + dcol;
    if (r < 0 || r >= SIZE || c < 0 || c >= SIZE || board[r][c].getpiece() == Position::EMPTY || board[r][c].getpiece() == cur.getpiece()) {
        return false;
    }

    // Check if there is a continuous line of opponent's pieces
    while (r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c].getpiece() != Position::EMPTY) {
        if (board[r][c].getpiece() == cur.getpiece()) {
            return true;
        }
        r += drow;
        c += dcol;
    }
    return false;
}

bool Board::isValidMove(int row, int col, Position piece) {
    // Check if the position is empty
    if (board[row][col].getpiece() != Position::EMPTY) {
        return false;
    }
    
    // Check if the move is adjacent to an opposing piece
    bool adjacentOpposingPiece = false;
    for (int i = row-1; i <= row+1; i++) {
        for (int j = col-1; j <= col+1; j++) {
            if (i >= 0 && i < SIZE && j >= 0 && j < SIZE && (i != row || j != col)) {
                if (board[i][j].getpiece() != cur.getpiece() && board[i][j].getpiece() != Position::EMPTY) {
                    adjacentOpposingPiece = true;
                }
            }
        }
    }
    if (!adjacentOpposingPiece) {
        return false;
    }
    
    // Check if the move would flip any pieces
    bool flipPieces = false;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i != 0 || j != 0) {
                if (checkDirection(row, col, i, j, piece)) {
                    flipPieces = true;
                    int r = row + i;
                    int c = col + j;
                    while (board[r][c].getpiece() != cur.getpiece()) {
                        board[r][c].setpiece(cur.getpiece());
                        r += i;
                        c += j;
                    }
                }
            }
        }
    }
    return flipPieces;
}



// Actual playing
void Board::play() {
    drawBoard();
    while (true)
    {
        int pick;
        std::cout << std:: endl << "1. Save" << std::endl << std::endl << "2. Concede" << std::endl << std::endl << "3. Make a Move" << std::endl << std::endl;
        cin >> pick;
        if (pick == 1)
        {
            save();
        }
        else if (pick == 2)
        {
            takeTurn();
            std::cout<< std:: endl << "You have conceded the game, the winner is " << cur.getname()<< std::endl;
            exit(0);
        }
        else if (pick == 3)
        {
            while (true)
            {
                std::cout << "Player 1: " << p1.getname()<< ". Color: " << p1.getpiece() <<std::endl;
                std::cout << "Player 2: " << p2.getname()<< ". Color: " << p2.getpiece() <<std::endl;
                std::cout << "Current Player: " << cur.getname()<< ". Color: " << cur.getpiece() <<std::endl;
                int nrow, ncol;
                std::cout<<std::endl<< "Enter row and col [row][col] to place a piece"<< std::endl;
                std::cin>> nrow;
                std::cin>> ncol;
                //board[nrow][ncol].setpiece(cur.getpiece());
                
                if (isValidMove(nrow, ncol, board[nrow][ncol]))
                {
                    board[nrow][ncol].setpiece(cur.getpiece());
                    break;
                }
                std::cout << "Enter a valid move";
            }
        }
            if (isFull())
            {
                getWinner();
            }
        drawBoard();
        takeTurn();
    }
}

// Load a saved game from a file
Board Board::load() {
    string name;
    std::cout<<"Enter saved file name: "<<std::endl;
    std::cin>>name;
    Board board(name);
    return board;
}






Board::Board(string save_file) {
    ifstream file(save_file);
    string line1, line2, line3, name1, name2, name3, line4;
    char piece1, piece2, piece3;
    std::getline(file, line1);
    std::getline(file, line2);
    std::getline(file, line3);
    std::stringstream ss1;
    std::stringstream ss2;
    std::stringstream ss3;
    ss1 >> name1 >> piece1;
    ss2 >> name2 >> piece2;
    ss3 >> name3 >> piece3;
    p1.setname(name1);
    p2.setname(name2);
    cur.setname(name3);
    p1.setpiece(piece1);
    p2.setpiece(piece2);
    cur.setpiece(piece3);
    if (piece1=='W')
    {
        p1.setpiece(Position::WHITE);
        p2.setpiece(Position::BLACK);
    }
    else
    {
        p2.setpiece(Position::WHITE);
        p1.setpiece(Position::BLACK);
    }
    if (p1.getname()==cur.getname())
    {
        cur.setpiece(p1.getpiece());
    }
    else
    {
        cur.setpiece(p2.getpiece());
    }
    
    std::getline(file, line4);
    
    int index = 0;

    // Traverse each row of the board array
    for (int row = 0; row < SIZE; row++) {
        // Traverse each column of the board array
        for (int col = 0; col < SIZE; col++) {
            board[row][col]=Position(row,col,Position::EMPTY);
            board[row][col].setpiece(line4[index]);
            index++;
        }
    }

}

void Board::save() {
    std::string filename;
    std::cout << "Enter filename to save"<< std::endl;
    std::cin >> filename;
    std::ofstream file(filename);
    file<<p1.getname()<<" "<<p1.getpiece()<<std::endl;
    file<<p2.getname()<<" "<<p2.getpiece()<<std::endl;
    file<<cur.getname()<<" "<<cur.getpiece()<<std::endl;
        if (file.is_open()) {
            for (int row = 0; row < SIZE; row++) {
                for (int col = 0; col < SIZE; col++) {
                    file << board[row][col].getpiece();
                }
            }
            std::cout << "Board saved to " << filename << std::endl;
        }
        else {
            std::cout << "Unable to open file " << filename << std::endl;
        }
        file.close();
    exit(0);
    
}
