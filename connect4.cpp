#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string>
using namespace std;
#define ROWS 6
#define COLS 7
#define red "\u001b[31;1m"
#define reset "\u001b[0m"
#define yellow "\u001b[33;1m"
#define magenta "\u001b[35;1m"
#define p1 red << player1 << reset
#define p2 yellow << player2 << reset


//functions header
char** initializeBoard();

void printBoard(char** board);

string chooseRandomPlayer(string name1, string name2);

bool checkValidInput (char** board, string input);

bool isNumeric(string s);

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
    char** board = initializeBoard();
    
    int turn = 1, win = 0, numberOfMoves = 0;

    while (win != 1 && numberOfMoves < ROWS * COLS) {
        if (turn == 1){
            cout << " ==" << p1 << "'s turn!==";
        }
        else {
            cout << " ==" << p2 << "'s turn!==";
        }

        printBoard(board);
        numberOfMoves++;
        turn = (turn == 1) ? 2 : 1;
    }

    
    string col;
    cin >> col;
    cout << checkValidInput(board, col);
    
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


bool checkValidInput (char** board, string input){
    bool number = isNumeric(input);
    if (!number){   //sequence of letters characters
        cout << magenta << "\nINVALID INPUT! INSERT A INTEGER NUMBER!" << reset;
        return false;
    }

    else if (number && input.size() >= 2){
        cout << magenta << "\nINVALID INPUT!  NUMBER SHOULD BE BETWEEN 1 AND 7!" << reset;
        return false;
    }

    else if (number && input.size() == 1) {
        int column_number = stoi(input);
        if (board[0][column_number] != 'O'){
            cout << magenta << "\nINVALID INPUT! COLUMN IS FULL!" << reset;
            return false;
        }
        else {
            return true;
        }
    }
    return false;
}
       

bool isNumeric(string s) {
    for (char c : s) {
        if (isdigit(c) == 0)
            return false;
    }
    return true;
}