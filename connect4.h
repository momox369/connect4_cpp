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



//functions header
string** initializeBoard();

void printBoard(string** board);

string chooseRandomPlayer(string name1, string name2);

bool validInput (string** board, string input);

void insertColumn(string**  board, int column_number, int turn);

//helper functions
bool isNumeric(string s);

bool isEqualToEmptyToken (string s);