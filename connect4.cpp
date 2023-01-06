#include <iostream>
#include <windows.h>
#include <stdlib.h>
using namespace std;
#define ROWS 6
#define COLS 7
#define red "\u001b[31m"
#define reset "\u001b[0m"
#define yellow "\u001b[33m"

char** initializeBoard();



int main() {
    //creating the board of the game
    char** board = initializeBoard();
    cout << "Board initialized!";
    
    return 0;
}

char** initializeBoard(){
    char** board = new char*[ROWS];
    for (int i = 0; i < ROWS; i++){
        board[i] = new char[COLS];
    }
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            board[i][j] = 'O';
        }
    }
    return board;
}



