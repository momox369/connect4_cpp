#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string>
using namespace std;

#define ROWS 6
#define COLS 7
#define player1_token "\u001b[31;1mX\u001b[0m"
#define player2_token "\u001b[33mX\u001b[0m"

//colors
#define red "\u001b[31;1m"
#define reset "\u001b[0m"
#define yellow "\u001b[33;1m"
#define magenta "\u001b[35;1m"
#define mcolored(x) magenta << x << reset
#define rcolored(x) red << x << reset
#define ycolored(x) yellow << x << reset

string player1, player2;
const int MAX_DEPTH = 5;
const int INF = 1e9;

//functions header
int** initializeBoard();

void printBoard(int** board);

string chooseRandomPlayer(string name1, string name2);

bool validInput (int** board, string input);

void insertColumn(int**  board, int column_number, int turn);

int checkWinnerningMove(int** board);

void announceWinner(int win, float t1, float t2);

void introConnect4();

int modeChooser();

int evaluateBoard(int** board);

bool isTerminalNode(int** board);

int minimax(int** board, int depth, int alpha, int beta, bool maximizingPlayer);

void undoMove(int** board, int col);

int botMove(int** board);

//helper functions
bool isNumeric(string s);

bool isEqualToEmptyToken (string s);

int which_player(string name);

bool isBotTurn(int turn);