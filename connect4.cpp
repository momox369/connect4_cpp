#include <iostream>
#include <windows.h>
#include <stdlib.h>
using namespace std;
#define ROWS 6
#define COLS 7
#define red "\u001b[31m"
#define reset "\u001b[0m"
#define yellow "\u001b[33m"
#define p1 red << player1 << reset
#define p2 yellow << player2 << reset

char** initializeBoard();

void printBoard(char** board);

string chooseRandomPlayer(string name1, string name2);

int main() {
    
    cout << red << "WELCOME TO " << reset << yellow << "CONNECT 4" << reset << " by maurice ;)\n";
    

    //Taking the players name and role
    string name1, name2;
    cout << "\nEnter player name: ";
    cin >> name1;

    cout << "Enter another player name: ";
    cin >> name2;

    string player1 = chooseRandomPlayer(name1, name2);
    string player2 = (player1.compare(name1) == 0) ? name2 : name1;
    cout << red << "\nPlayer 1 is: " << player1;
    cout << yellow << "\nPlayer 2 is: " << player2 << reset << "\n\n"; 

    //creating the board for the game
    cout << " ==" << p1 << "'s turn!==";
    char** board = initializeBoard();
    printBoard(board);

    


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

void printBoard(char** board) {
    cout << "\n";
    
    for (int i = 0; i < ROWS; i++){
        cout << "| ";
        for (int j = 0; j < COLS; j++){
            cout << board[i][j] << " ";
        }
        cout << "|\n"; 
    }
    cout << "-----------------";
}

string chooseRandomPlayer(string name1, string name2) {
    /*
    if random number is even, return name1
    else if random number is odd, return name2.

    -require: names of the players
    -effects: return a random player name with 50% | 50% chances each
    */
    
    srand(time(0));
    int random = rand() % 10;
    return (random % 2 == 0) ? name1 : name2; 
}